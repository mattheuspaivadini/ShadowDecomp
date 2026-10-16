/* STATUS (Session 4, 2026-10-14): NON_MATCHING. ee-gcc software-pipelines the 256-entry table scan (the value is loaded one iteration ahead and the index is saved before the increment). Plain for/while/do-while + break yields a bounds-first loop; both revisions and -g0 tried.
 * The original .s stays in the build (asm/cod/002790.s); this C
 * attempt is kept for the record. */
/* asm/cod/002790.s -> func_00102790 @ 0x00102790 (0x4C bytes)
 *   lui   $v1, %hi(D_0013B790)
 *   daddu $a2, $zero, $zero
 *   addiu $a4, $v1, %lo(D_0013B790)   ; p = D
 *   lw    $v0, 0x0($a4)
 * .L001027A0:
 *   addiu $a4, $a4, 0x4                ; p++
 *   daddu $a3, $a2, $zero              ; idx = i
 *   addiu $a2, $a2, 0x1                ; i++
 *   bltz  $v0, .L001027C8
 *    slti $a1, $a2, 0x100              ; i < 256
 *   bnel  $a1, $zero, .L001027A0
 *    lw   $v0, 0x0($a4)
 *   addiu $a3, $zero, -0x1             ; idx = -1 (table full)
 * .L001027C8:
 *   addiu $v1, $v1, %lo(D_0013B790)
 *   sll   $v0, $a3, 2
 *   addu  $v0, $v0, $v1
 *   jr    $ra
 *    sw   $a0, 0x0($v0)                ; D[idx] = value
 *
 * Store `value` at the first negative entry of the 256-int table D_0013B790,
 * or at index -1 if none is negative.
 */
extern int D_0013B790[256];

void LoaderSysEntryExternalThreadList(int value) {
    int i = 0;

    while (D_0013B790[i] >= 0) {
        i++;
        if (i >= 256) {
            i = -1;
            break;
        }
    }
    D_0013B790[i] = value;
}
