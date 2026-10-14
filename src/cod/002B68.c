/* asm/cod/002B68.s -> func_00102B68 @ 0x00102B68 (0x6C bytes, 27 insns)
 *
 * Free every live slot of the D_0013B790 table (same 256-entry table as
 * func_00102A80 / the matched func_001028F0):
 *
 *   addiu $s0,$v0,%lo(D_0013B790)     ; p = D_0013B790
 *   addiu $s1,$zero,0xFF              ; i = 0xFF
 *   addiu $s2,$zero,-1                ; value = -1 (kept across both calls)
 * .Lloop:
 *   lw    $v0,0x0($s0)
 *   bltz  $v0,.Lskip / daddu $a0,$v0  ; if (v >= 0) ...
 *   jal   func_00106E30 / nop         ;   teardown
 *   jal   func_00106DF0 / lw $a0,0x0($s0)   ;   release (value re-loaded)
 *   sw    $s2,0x0($s0)                ;   *p = -1
 * .Lskip:
 *   addiu $s1,$s1,-1
 *   bgez  $s1,.Lloop / addiu $s0,$s0,0x4    ; p++ in the branch slot
 *
 * The `-1` is materialised before the loop into $s2, i.e. a local initialised
 * before the loop (the func_00102A00 idiom); the second callee gets a fresh
 * `*p` load, so the source passes the dereference, not the test variable.
 * Same body as the inner loop of func_00102608 (asm/cod/002608.s).
 * MATCH GUESS: cc=296 (saves 8 bytes apart; the 0028F0/002C58 table family is
 * 296) */
extern int D_0013B790[256];

void func_00106E30(int a0);
void func_00106DF0(int a0);

void func_00102B68(void) {
    int value = -1;
    int i;
    int *p = D_0013B790;

    for (i = 0xFF; i >= 0; i--) {
        int v = *p;

        if (v >= 0) {
            func_00106E30(v);
            func_00106DF0(*p);
            *p = value;
        }
        p++;
    }
}
