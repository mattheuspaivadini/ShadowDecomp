/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 2 [cc=29, default].
 * 3-way memcmp + flag; 00E338 is its clone.
 * The original .s stays in the build (asm/cod/00AAC8.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/00AAC8.s -> func_0010AAC8 @ 0x0010AAC8 (0x8C bytes, 35 insns)
 *
 * Three-way memcmp (func_00128188 = `sltiu $v0,$a2,0x10` + the 128-bit pxor
 * scan) over the two fixed 4-byte id words D_001470E8 / D_0013227C and the
 * runtime word D_00132328:
 *
 *   r = 0;
 *   if (memcmp(D_001470E8, D_0013227C, 4)        != 0)   ; $a0/$a1/$a2 = 4
 *       if (memcmp(D_001470E8, D_00132328, 4)    != 0)
 *           r = memcmp(D_0013227C, D_00132328, 4) != 0;  ; sltu $s2,$zero,$v0
 *   return r;
 *
 * D_00132328 is re-loaded for the second and third call (the `lw` in the
 * `beqz` delay slot plus the re-load in the next call's slot), and its `lui`
 * half lives in $s0 for both, so it is a non-small 4-byte scalar addressed
 * with lui/%lo. The first comparison is `beqz`-guarded (equal -> return 0).
 * MATCH GUESS: cc=29 (0x0010Axxx is inside the 2.9 block whose frames keep the
 * 16-byte-stride $s0..$s3 saves) */
extern char D_0013227C[];   /* .data/.bss 4-byte id word (lui/addiu) */
extern char D_001470E8[];   /* .data/.bss 4-byte id word (lui/addiu) */
extern int  D_00132328[];   /* 4-byte scalar; `lw %lo(..)($s0)` -> non-small */

int func_00128188(void *a0, void *a1, int a2);

int func_0010AAC8(void) {
    int r = 0;

    if (func_00128188(D_001470E8, D_0013227C, 4) != 0) {
        if (func_00128188(D_001470E8, (void *)D_00132328[0], 4) != 0) {
            r = func_00128188(D_0013227C, (void *)D_00132328[0], 4) != 0;
        }
    }
    return r;
}
