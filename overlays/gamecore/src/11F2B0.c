/* GAMECORE.XFF @ 0x11F2B0 (56 B) - SCRConditionLessRandomVal
 * Evidence: stores $f20, 0x8($sp), $ra, 0x0($sp); loads $f0, 0x40B4($v0), $ra, 0x0($sp), $f20, 0x8($sp); calls getSCRDataCtrlWork; frame
 
 */
char *getSCRDataCtrlWork(void);

int SCRConditionLessRandomVal(float t) {
    return *(float *)(getSCRDataCtrlWork() + 0x40B4) <= t;
}
