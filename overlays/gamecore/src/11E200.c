/* GAMECORE.XFF @ 0x11E200 (56 B) - SCRConditionOrientLapsedTime
 * Evidence: stores $f20, 0x8($sp), $ra, 0x0($sp); loads $f0, 0x40A8($v0), $ra, 0x0($sp), $f20, 0x8($sp); calls getSCRDataCtrlWork; frame
 
 */
char *getSCRDataCtrlWork(void);

int SCRConditionOrientLapsedTime(float t) {
    return t <= *(float *)(getSCRDataCtrlWork() + 0x40A8);
}
