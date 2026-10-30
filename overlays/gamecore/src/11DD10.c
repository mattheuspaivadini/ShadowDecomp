/* GAMECORE.XFF @ 0x11DD10 (36 B) - SCRConditionPlayerInLost
 * Evidence: stores $ra, 0x0($sp); loads $v0, 0x405C($v0), $ra, 0x0($sp); calls getSCRDataCtrlWork; frame
 
 */
/* UNCONFIRMED: +0x405C is the "lost player" timer. */
char *getSCRDataCtrlWork(void);

int SCRConditionPlayerInLost(void) {
    return *(int *)(getSCRDataCtrlWork() + 0x405C) == 0;
}
