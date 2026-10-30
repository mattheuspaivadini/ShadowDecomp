/* GAMECORE.XFF @ 0x1183B0 (48 B) - SCRFuncAddAngryValue
 * Evidence: stores $ra, 0x0($sp), $f20, 0x8($sp), $f0, 0x40F8($v0); loads $f0, 0x40F8($v0), $ra, 0x0($sp), $f20, 0x8($sp); calls getSCRDataCtrlWork; frame
 
 */
/* UNCONFIRMED: adds to the script angry value at +0x40F8. */
char *getSCRDataCtrlWork(void);

void SCRFuncAddAngryValue(float value) {
    *(float *)(getSCRDataCtrlWork() + 0x40F8) += value;
}
