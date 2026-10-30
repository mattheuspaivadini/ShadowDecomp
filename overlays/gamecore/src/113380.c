/* GAMECORE.XFF @ 0x113380 (56 B) - SCRConditionLessAngryValue
 * Evidence: stores $f20, 0x8($sp), $ra, 0x0($sp); loads $f0, 0x40F8($v0), $ra, 0x0($sp), $f20, 0x8($sp); calls getSCRDataCtrlWork; frame
 
 */
/* UNCONFIRMED: same field as SCRConditionOverAngryValue, opposite sense. */
char *getSCRDataCtrlWork(void);

int SCRConditionLessAngryValue(float value) {
    if (*(float *)(getSCRDataCtrlWork() + 0x40F8) <= value)
        return 1;
    return 0;
}
