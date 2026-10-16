/* STATUS (Session 4, 2026-10-14): NON_MATCHING. block layout: the original branches `bgez` to the normal path with the error return inline; ours inlines the normal path and branches to the error.
 * The original .s stays in the build (asm/cod/010EF0.s); this C
 * attempt is kept for the record. */
/* asm/cod/010EF0.s -> func_00110EF0 @ 0x00110EF0 (0x50 bytes)
 *   lui   $v0, %hi(D_00133918)
 *   addiu $v1, $v0, %lo(D_00133918)   ; base
 *   lw    $v0, 0x8($v1)
 *   bgez  $v0, .L00110F10
 *    nop
 *   lui   $v0, (0x80008001 >> 16)
 *   jr    $ra
 *    ori  $v0, $v0, (0x80008001 & 0xFFFF)
 * .L00110F10:
 *   beqz  $a0, .L00110F20
 *    nop
 *   lw    $v0, 0x10($v1)
 *   sw    $v0, 0x0($a0)
 * .L00110F20:
 *   beqz  $a1, .L00110F38
 *    nop
 *   lw    $v1, 0x10($v1)
 *   addiu $v0, $zero, 0x80
 *   subu  $v0, $v0, $v1
 *   sw    $v0, 0x0($a1)
 * .L00110F38:
 *   jr    $ra
 *    daddu $v0, $zero, $zero
 *
 * If the counter field08 is negative, return the 0x80008001 error; otherwise
 * optionally write field10 and (0x80 - field10) to the two output pointers.
 */
struct S00133918 {
    char pad00[0x08];
    int  field08;   /* 0x08 */
    int  field0C;   /* 0x0C */
    int  field10;   /* 0x10 */
};

extern struct S00133918 D_00133918;

int iGetTimerUsedUnusedCounters(int *out0, int *out1) {
    if (D_00133918.field08 >= 0) {
        if (out0)
            *out0 = D_00133918.field10;
        if (out1)
            *out1 = 0x80 - D_00133918.field10;
        return 0;
    }
    return 0x80008001;
}
