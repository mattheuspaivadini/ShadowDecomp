/* GAMECORE.XFF @ 0x11F798 (52 B) - SCRConditionPPCheck
 * Evidence: stores $ra, 0x0($sp); loads $a1, 0x3C90($a0), $a2, 0x3C8C($a0), $ra, 0x0($sp); calls getSCRDataCtrlWork, getConnectPPointIdx; frame
 
 */
char *getSCRDataCtrlWork(void);
/* UNCONFIRMED: callee argument list inferred from $a1/$a2 loads. */
int getConnectPPointIdx(char *work, int a, int b);

int SCRConditionPPCheck(void) {
    char *w = getSCRDataCtrlWork();
    return getConnectPPointIdx(w, *(int *)(w + 0x3C90),
                               *(int *)(w + 0x3C8C)) >= 2;
}
