/* asm/cod/011D60.s -> func_00111D60 @ 0x00111D60 (0x90 bytes, 36 insns)
 *
 * V-blank handshake (docs/structs.md: 0x1000F000 = EE INTC `I_STAT`, bit 2 =
 * the VSS/V-blank-start cause, write 4 = clear) wrapped twice in the
 * func_0010FB20/func_0010FB70 guard pair:
 *
 *   g = func_0010FB20();
 *   I_STAT = 4;                                ; addiu $a0,$zero,4 ; sw
 *   sync
 *   if (g) func_0010FB70();
 *   while ((I_STAT & 4) == 0) ;                ; `beqz` -> poll the bit
 *   g = func_0010FB20();
 *   I_STAT = 4;
 *   sync
 *   if (g) func_0010FB70();                    ; sibling `j`, epilogue before
 *
 * The register base is kept in $v1 and re-materialised ($lui twice, one $ori
 * shared) after the calls; the second release is the last statement, so it is
 * a bare `j func_0010FB70`. The `lui`-in-the-delay-slot and the 8-byte-spaced
 * $ra frame match the surrounding 0x0011Dxxx block (011D50 is cc=296).
 * MATCH GUESS: cc=296 */
#include "symbols.h"

#define EE_INTC_I_STAT 0x1000F000u   /* EE INTC status (write-1-to-clear) */

int  DIntr(void);
void EIntr(void);

void VSync(void) {
    int g;

    g = DIntr();
    HWREG(EE_INTC_I_STAT) = 4;
    __asm__ __volatile__("sync" ::: "memory");
    if (g != 0)
        EIntr();
    while ((HWREG(EE_INTC_I_STAT) & 4) == 0)
        ;
    g = DIntr();
    HWREG(EE_INTC_I_STAT) = 4;
    __asm__ __volatile__("sync" ::: "memory");
    if (g != 0)
        EIntr();
}
