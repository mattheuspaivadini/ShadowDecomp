/* GAMECORE.XFF @ 0x11DC80 (52 B) - SCRConditionPathPassageNum
 * Evidence: stores $s0, 0x0($sp), $ra, 0x8($sp); loads $ra, 0x8($sp), $s0, 0x0($sp); calls getSCRDataCtrlWork, getPassageNum; frame
 
 */
/* UNCONFIRMED: the count is the 2nd script argument. */
char *getSCRDataCtrlWork(void);
int getPassageNum(char *work);

int SCRConditionPathPassageNum(void *unused, int num) {
    return num == getPassageNum(getSCRDataCtrlWork());
}
