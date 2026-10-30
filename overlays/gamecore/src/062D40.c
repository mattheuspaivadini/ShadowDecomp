/* GAMECORE.XFF @ 0x062D40 (36 B) - SCRFuncKirinCameraNeckDownIdSet
 * Evidence: `jal GetLayoutClass`, then `sw 0xA` into the result +0x1AC.
 * UNCONFIRMED: the layout field meaning (a camera neck-down id) and the callee
 * prototype (called with no arguments).
 
 */
void *GetLayoutClass(void);

void SCRFuncKirinCameraNeckDownIdSet(void) {
    *(int *)((char *)GetLayoutClass() + 0x1AC) = 0xA;
}
