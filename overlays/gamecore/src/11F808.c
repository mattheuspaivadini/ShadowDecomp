/* GAMECORE.XFF @ 0x11F808 (56 B) - SCRConditionEyeModeLapsedTime
 * Evidence: stores $f20, 0x8($sp), $ra, 0x0($sp); loads $f0, 0x4108($v0), $ra, 0x0($sp), $f20, 0x8($sp); calls getSCRDataCtrlWork; frame
 
 */
char *getSCRDataCtrlWork(void);

int SCRConditionEyeModeLapsedTime(float t) {
    return t <= *(float *)(getSCRDataCtrlWork() + 0x4108);
}
