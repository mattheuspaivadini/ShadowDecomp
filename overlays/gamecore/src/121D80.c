/* GAMECORE.XFF @ 0x121D80 (48 B) - SCRConditionHintOverPlayCount
 * Evidence: stores $s0, 0x0($sp), $ra, 0x8($sp); loads $v0, 0x40E8($v0), $ra, 0x8($sp), $s0, 0x0($sp); calls getSCRDataCtrlWork; frame
 
 */
char *getSCRDataCtrlWork(void);

int SCRConditionHintOverPlayCount(void *unused, int num) {
    return *(int *)(getSCRDataCtrlWork() + 0x40E8) >= num;
}
