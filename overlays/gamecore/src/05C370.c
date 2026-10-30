/* GAMECORE.XFF @ 0x05C370 (32 B) - SCRConditionHorseCalled
 * Evidence: a0 = [v0+0x4078], sibling j IsHorseCalled_withFlgOff
 * UNCONFIRMED: none
 */
char *getSCRDataCtrlWork(void);
int IsHorseCalled_withFlgOff(int f);

int SCRConditionHorseCalled(void) {
    return IsHorseCalled_withFlgOff(*(int *)(getSCRDataCtrlWork() + 0x4078));
}
