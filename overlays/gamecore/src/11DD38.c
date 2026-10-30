/* GAMECORE.XFF @ 0x11DD38 (36 B) - SCRConditionInstantaneousPlayerInSight
 * Evidence: stores $ra, 0x0($sp); loads $v0, 0x4060($v0), $ra, 0x0($sp); calls getSCRDataCtrlWork; frame
 
 */
/* UNCONFIRMED: +0x4060 is a 64-bit "in sight" flag word. */
char *getSCRDataCtrlWork(void);

int SCRConditionInstantaneousPlayerInSight(void) {
    return *(long long *)(getSCRDataCtrlWork() + 0x4060) != 0;
}
