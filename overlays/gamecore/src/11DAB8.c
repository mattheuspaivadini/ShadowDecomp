/* GAMECORE.XFF @ 0x11DAB8 (52 B) - SCRConditionPPPassageNum
 * Evidence: stores $s0, 0x0($sp), $ra, 0x8($sp); loads $ra, 0x8($sp), $s0, 0x0($sp); calls getSCRDataCtrlWork, getPPointPasasgeNum; frame
 
 */
/* UNCONFIRMED: the count is the 2nd script argument; compares it with the
 * passage point passage count.
 */
char *getSCRDataCtrlWork(void);
int getPPointPasasgeNum(char *work);

int SCRConditionPPPassageNum(void *unused, int num) {
    return num == getPPointPasasgeNum(getSCRDataCtrlWork());
}
