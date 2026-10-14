/* asm/cod/002A80.s -> func_00102A80 @ 0x00102A80 (0x6C bytes, 27 insns)
 *
 * Walk the 256-entry int table D_0013B790 and hand every live entry (any value
 * != -1) to the visitor callback received in $a0:
 *
 *   addiu $s0,$zero,0xFF                  ; i = 0xFF (the counter)
 *   addiu $s3,$zero,-1                    ; the "empty slot" value, kept across
 *                                         ; the indirect call
 *   lw    $v0,0x0($s1)                    ; pre-load of *p
 * .Lloop:
 *   addiu $s1,$s1,0x4                     ; p++ (the load was rotated down)
 *   beq   $v0,$s3,.Lskip / daddu $a0,$v0  ; if (v != -1) callback(v)
 *   jalr  $s2 / nop
 * .Lskip:
 *   addiu $s0,$s0,-1
 *   bgezl $s0,.Lloop / lw $v0,0x0($s1)    ; loop back, next load in the slot
 *
 * So the body is `v = *p++; if (v != -1) cb(v);` with the counter decrementing
 * in the loop tail; `-1` is loop-invariant and therefore lives in $s3.  The
 * callee pointer is $s2 (the incoming $a0 moved to a callee-saved register) and
 * the callback argument is the entry value.
 * MATCH GUESS: cc=296 (saves 8 bytes apart, same table family as the matched
 * 0028F0/002930, which 002C58 proves is 296; nop in the `jalr` shadow) */
extern int D_0013B790[256];

void func_00102A80(void (*cb)(int)) {
    int i;
    int *p = D_0013B790;

    for (i = 0xFF; i >= 0; i--) {
        int v = *p++;

        if (v != -1)
            cb(v);
    }
}
