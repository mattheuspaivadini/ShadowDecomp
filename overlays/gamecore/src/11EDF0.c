/* GAMECORE.XFF @ 0x11EDF0 (56 B) - SCRConditionAttackPassageTime
 * Evidence: stores $f20, 0x8($sp), $ra, 0x0($sp); loads $f0, 0x40D0($v0), $ra, 0x0($sp), $f20, 0x8($sp); calls getSCRDataCtrlWork; frame
 
 */
char *getSCRDataCtrlWork(void);

int SCRConditionAttackPassageTime(float t) {
    return t <= *(float *)(getSCRDataCtrlWork() + 0x40D0);
}
