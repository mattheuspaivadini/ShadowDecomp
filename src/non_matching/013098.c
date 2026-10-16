/* STATUS (Session 4, 2026-10-14): NON_MATCHING. arena step; the load order of field00/field08 differs.
 * The original .s stays in the build (asm/cod/013098.s); this C
 * attempt is kept for the record. */
/* asm/cod/013098.s -> func_00113098 @ 0x00113098 (0x58 bytes)
 *   lw    $a1, 0x0($a0)                ; p = a0->field00
 *   andi  $v0, $a1, 0xC
 *   beqz  $v0, .L001130C4
 *    lw   $a2, 0x8($a0)                ; s = a0->field08
 * .L001130A8:
 *   sw    $zero, 0x0($a1)              ; *p = 0
 *   addiu $a1, $a1, 0x4
 *   andi  $v0, $a1, 0xC
 *   bnez  $v0, .L001130A8
 *    nop
 * .L001130C4:
 *   beqz  $a2, .L001130E0
 *    subu $v0, $a1, $a2                ; (delay) p - s
 *   lw    $v1, 0x0($a2)
 *   sra   $v0, $v0, 4
 *   addiu $v0, $v0, -0x1
 *   addu  $v1, $v1, $v0
 *   sw    $v1, 0x0($a2)
 * .L001130E0:
 *   sw    $zero, 0x8($a0)
 *   daddu $v0, $a1, $zero
 *   jr    $ra
 *    sw   $a1, 0x0($a0)                ; a0->field00 = p
 *
 * Zero the words until the pointer is 16-byte aligned, then, if a saved block
 * pointer is present, credit it with the number of 16-byte units skipped.
 * Semantics UNCONFIRMED (a pool/arena allocator step).
 */
struct A00113098 {
    int  field00;   /* 0x00 current pointer */
    int  field04;   /* 0x04 */
    int  field08;   /* 0x08 saved block */
};

int sceVif1PkTerminate(struct A00113098 *a0) {
    int *p = (int *)a0->field00;
    struct A00113098 *s = (struct A00113098 *)a0->field08;

    while ((unsigned int)p & 0xC) {
        *p = 0;
        p++;
    }
    if (s)
        s->field00 += (int)((char *)p - (char *)s) / 16 - 1;
    a0->field08 = 0;
    a0->field00 = (int)p;
    return (int)p;
}
