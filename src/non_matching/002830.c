/* STATUS (Session 4, 2026-10-14): NON_MATCHING. same pipelined table-scan family (first zero entry).
 * The original .s stays in the build (asm/cod/002830.s); this C
 * attempt is kept for the record. */
/* asm/cod/002830.s -> func_00102830 @ 0x00102830 (0x70 bytes)
 *   beqz  $a0, .L00102898             ; value == 0 -> return -1
 *    lui  $a2, %hi(D_0013C790)
 *   daddu $v1, $zero, $zero
 *   addiu $a1, $a2, %lo(D_0013C790)
 *   lw    $v0, 0x0($a1)
 * .L00102848:
 *   beqz  $v0, .L00102890             ; first zero entry
 *    addiu $a1, $a1, 0x4
 *   addiu $v1, $v1, 0x1
 *   slti  $v0, $v1, 0x100
 *   bnel  $v0, $zero, .L00102848
 *    lw   $v0, 0x0($a1)
 *   addiu $a1, $zero, -0x1
 * .L00102870:
 *   bltz  $a1, .L00102898
 *    sll  $v1, $a1, 2
 *   addiu $v0, $a2, %lo(D_0013C790)
 *   addu  $v1, $v1, $v0
 *   daddu $v0, $a1, $zero
 *   jr    $ra
 *    sw   $a0, 0x0($v1)                ; D[idx] = value
 * .L00102890:
 *   b     .L00102870
 *    daddu $a1, $v1, $zero
 * .L00102898:
 *   jr    $ra
 *    addiu $v0, $zero, -0x1
 *
 * Store `value` (non-zero) at the first zero entry of the 256-int table
 * D_0013C790, return its index; -1 when value is 0 or the table is full.
 */
extern int D_0013C790[256];

int LoaderSysEntryExternalIopMemoryList(int value) {
    int i;

    if (value == 0)
        return -1;
    for (i = 0; i < 256; i++) {
        if (D_0013C790[i] == 0) {
            D_0013C790[i] = value;
            return i;
        }
    }
    return -1;
}
