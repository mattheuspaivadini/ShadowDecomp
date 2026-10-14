/* MATCHING (Session 4, 2026-10-14): byte-exact only with the ALTERNATE EE-GCC
 * revision `ee-gcc2.9-991111-01` (manifest token `cc=29`); the original keeps
 * the error path falling through. Evidence: tools/cc_matrix.py,
 * docs/compiler.md section 4.3.
 *
 * asm/cod/010640.s -> func_00110640 @ 0x00110640 (0x2C bytes)
 *   lui   $v0, %hi(D_00133920)
 *   lw    $v1, %lo(D_00133920)($v0)
 *   bgez  $v1, .L0011065C
 *    lui  $v1, (0x10001010 >> 16)        <- branch delay slot
 *   lui   $v0, (0x80008001 >> 16)
 *   jr    $ra
 *    ori  $v0, $v0, (0x80008001 & 0xFFFF)
 * .L0011065C:
 *   ori   $v1, $v1, (0x10001010 & 0xFFFF)
 *   lw    $v0, 0x0($v1)
 *   jr    $ra
 *    andi $v0, $v0, 0x3
 *
 * D_00133920 is in .data, i.e. outside the gp window -> absolute addressing.
 * 0x10001010 is the EE **Timer 2 MODE register** (`EE_T2_MODE`, identified in
 * Session 4 step 5: ps2sdk `ee/kernel/include/timer.h`, ps2sdk
 * `common/include/ee_regs.h`, PCSX2 `Hw.h` RCNT2_MODE, PS2Tek "EE Timers"), so
 * this returns `MODE & 3` = the timer's clock source (0 = bus clock,
 * 1 = /16, 2 = /256, 3 = HBLANK). 0x80008001 is an error sentinel.
 * See docs/structs.md section "Hardware registers".
 */
#include "symbols.h"

int func_00110640(void) {
    if (D_00133920 < 0) {
        return 0x80008001;
    }
    return HWREG(EE_T2_MODE) & 3;
}
