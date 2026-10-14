/* Minimal probe: does Debian mips-linux-gnu-ld relax an out-of-range
 * %gp_rel reference into lui/%lo absolute addressing?
 *
 * Original func_00111D50 (0x00111D50) is:
 *   lui  $v0, %hi(D_00133940)
 *   jr   $ra
 *    sw  $zero, %lo(D_00133940)($v0)
 * with _gp = 0x00141D70 and D_00133940 = 0x00133940 (OUTSIDE the gp window
 * [0x00139D70, 0x00149D6F]).
 */
    .set noreorder
    .text
    .globl probe
probe:
    jr    $ra
    sw    $zero, %gp_rel(D_00133940)($gp)
