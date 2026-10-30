/* GAMECORE.XFF @ 0x113348 (56 B) - SCRConditionOverAngryValue
 * Evidence: stores $f20, 0x8($sp), $ra, 0x0($sp); loads $f0, 0x40F8($v0), $ra, 0x0($sp), $f20, 0x8($sp); calls getSCRDataCtrlWork; frame
 
 */
/* UNCONFIRMED: +0x40F8 is the script angry value. */
char *getSCRDataCtrlWork(void);

int SCRConditionOverAngryValue(float value) {
    if (value <= *(float *)(getSCRDataCtrlWork() + 0x40F8))
        return 1;
    return 0;
}
