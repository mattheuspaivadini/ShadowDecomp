/* GAMECORE.XFF @ 0x062D68 (32 B) - SCRFuncKirinCameraNeckDownIdReset
 * Evidence: jal GetLayoutClass; sw zero -> [v0+0x1AC]
 * UNCONFIRMED: none
 */
char *GetLayoutClass(void);

void SCRFuncKirinCameraNeckDownIdReset(void) {
    *(int *)(GetLayoutClass() + 0x1AC) = 0;
}
