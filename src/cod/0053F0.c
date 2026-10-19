/* asm/cod/0053F0.s -> func_001053F0.
 * Frame + sibling call iSignalSema(D_0013A188) on the split .sbss sema word (Session 28).
 * MATCHED. */
extern int D_0013A188;              /* sema id (.sbss), cf. 0050B8/0052D8 */

int iSignalSema(int sema);

void func_001053F0(void) {
    iSignalSema(D_0013A188);
}
