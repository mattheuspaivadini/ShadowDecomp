/* GAMECORE.XFF @ 0x118388 (40 B) - SCRFuncSetAngryValue
 * Evidence: stores $ra, 0x0($sp), $f20, 0x8($sp), $f20, 0x40F8($v0); loads $ra, 0x0($sp), $f20, 0x8($sp); calls getSCRDataCtrlWork; frame
 
 */
/* UNCONFIRMED: +0x40F8 is the script angry value. */
char *getSCRDataCtrlWork(void);

void SCRFuncSetAngryValue(float value) {
    *(float *)(getSCRDataCtrlWork() + 0x40F8) = value;
}
