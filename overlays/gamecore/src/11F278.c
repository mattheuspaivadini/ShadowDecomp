/* GAMECORE.XFF @ 0x11F278 (56 B) - SCRConditionOverRandomVal
 * Evidence: stores $f20, 0x8($sp), $ra, 0x0($sp); loads $f0, 0x40B4($v0), $ra, 0x0($sp), $f20, 0x8($sp); calls getSCRDataCtrlWork; frame
 
 */
char *getSCRDataCtrlWork(void);

int SCRConditionOverRandomVal(float t) {
    return t <= *(float *)(getSCRDataCtrlWork() + 0x40B4);
}
