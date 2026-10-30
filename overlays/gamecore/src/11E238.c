/* GAMECORE.XFF @ 0x11E238 (56 B) - SCRConditionVolumeTime0
 * Evidence: stores $f20, 0x8($sp), $ra, 0x0($sp); loads $f0, 0x40AC($v0), $ra, 0x0($sp), $f20, 0x8($sp); calls getSCRDataCtrlWork; frame
 
 */
char *getSCRDataCtrlWork(void);

int SCRConditionVolumeTime0(float t) {
    return t <= *(float *)(getSCRDataCtrlWork() + 0x40AC);
}
