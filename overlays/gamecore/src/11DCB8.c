/* GAMECORE.XFF @ 0x11DCB8 (52 B) - SCRConditionPathPassageNumOver
 * Evidence: stores $s0, 0x0($sp), $ra, 0x8($sp); loads $s0, 0x0($sp), $ra, 0x8($sp); calls getSCRDataCtrlWork, getPassageNum; frame
 
 */
/* UNCONFIRMED: true when the passage count reached the 2nd script argument. */
char *getSCRDataCtrlWork(void);
int getPassageNum(char *work);

int SCRConditionPathPassageNumOver(void *unused, int num) {
    return getPassageNum(getSCRDataCtrlWork()) >= num;
}
