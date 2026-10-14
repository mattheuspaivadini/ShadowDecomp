/* asm/cod/022E18.s -> func_00122E18 @ 0x00122E18 (0x4C bytes, 19 insns)
 *
 * Same transfer family as the matched func_00122D68 (0x64) / func_00122DA0
 * (0x65): func_001221D0() first, then two words of the D_00167F00 block are
 * filled (0x8 = the argument, 0x4 = D_00135958) and the block is handed to
 * func_00123260 together with D_00167EC0 and the command byte 0x67; the
 * callee's result is returned.
 *
 * The store order follows the asm (`sw s0,0x8(a1)` then `sw v0,0x4(a1)`), and
 * the argument survives the first call in a callee-saved register, so the frame
 * is 0x20 with $s0 + $ra.
 * MATCH GUESS: cc=29 (022DA0 twin, which is the manifest's cc=29 entry)
 */
#include "symbols.h"

int func_001221D0(void);
int func_00123260(char *dst, char *src, int n);

extern char D_00167EC0[];
extern int D_00167F00[];

int func_00122E18(int a0) {
    func_001221D0();
    D_00167F00[2] = a0;
    D_00167F00[1] = D_00135958;
    return func_00123260(D_00167EC0, (char *)D_00167F00, 0x67);
}
