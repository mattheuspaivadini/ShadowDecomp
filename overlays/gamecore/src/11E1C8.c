/* GAMECORE.XFF @ 0x11E1C8 (56 B) - SCRConditionModeLapsedTime
 * Evidence: stores $f20, 0x8($sp), $ra, 0x0($sp); loads $f0, 0x40A4($v0), $ra, 0x0($sp), $f20, 0x8($sp); calls getSCRDataCtrlWork; frame
 
 */
char *getSCRDataCtrlWork(void);

int SCRConditionModeLapsedTime(float t) {
    return t <= *(float *)(getSCRDataCtrlWork() + 0x40A4);
}
