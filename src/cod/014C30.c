/* asm/cod/014C30.s -> func_00114C30 @ 0x00114C30 (0x14 bytes)
 *   lui   $v1, (0x1000E060 >> 16)
 *   ori   $v1, $v1, (0x1000E060 & 0xFFFF)
 *   lw    $v0, 0x0($v1)
 *   jr    $ra
 *    sw   $a0, 0x0($v1)
 *
 * A read-modify-write of one EE hardware register, i.e. a volatile access that
 * returns the previous value. The address is the EE **DMAC Stall Address
 * register** (`EE_D_STADR`, identified in Session 4 step 5 against ps2sdk
 * `ee/dma/include/dma_registers.h` DMA_REG_STADR, ps2sdk `common/include/
 * ee_regs.h` A_EE_D_STADR and PCSX2 `Hw.h` DMAC_STADR): the routine reads the
 * stall address, writes a new one and returns the old, i.e. a "get/set stall
 * address" pair. The 32-bit width is evidenced by the `lw`/`sw` pair.
 * See docs/structs.md section "Hardware registers".
 * UNCONFIRMED: the SDK name of this routine (it is unreferenced in this image,
 * like several other libdma helpers - tools/ref_check.py, 0 references).
 */
#include "symbols.h"

unsigned int func_00114C30(unsigned int value) {
    unsigned int old = HWREG(EE_D_STADR);
    HWREG(EE_D_STADR) = value;
    return old;
}
