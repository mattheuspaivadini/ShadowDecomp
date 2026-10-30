/* GAMECORE.XFF @ 0x121DB0 (48 B) - SCRConditionHintEqualPlayCount
 * Evidence: stores $s0, 0x0($sp), $ra, 0x8($sp); loads $v1, 0x40E8($v0), $ra, 0x8($sp), $s0, 0x0($sp); calls getSCRDataCtrlWork; frame
 
 */
char *getSCRDataCtrlWork(void);

int SCRConditionHintEqualPlayCount(void *unused, int num) {
    return num == *(int *)(getSCRDataCtrlWork() + 0x40E8);
}
