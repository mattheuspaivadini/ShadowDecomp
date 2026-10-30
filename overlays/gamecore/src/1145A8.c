/* GAMECORE.XFF @ 0x1145A8 (52 B) - createAttackWork
 * Evidence: stores $s0, 0x0($sp), $ra, 0x8($sp), $zero, 0x14($v0), $zero, 0x0($v0); loads $ra, 0x8($sp), $s0, 0x0($sp); calls getSCRDataCtrlWork, j <.text>; frame
 
 */
/* UNCONFIRMED: +0x40C0 is the attack work block; +0x00/+0x14 are reset here
 * before the tail call into the shared initialiser at 0x1145E0.
 */
char *getSCRDataCtrlWork(void);
void func_1145E0(char *p);

void createAttackWork(char *p) {
    char *work = getSCRDataCtrlWork() + 0x40C0;
    *(int *)(work + 0x00) = 0;
    *(int *)(work + 0x14) = 0;
    func_1145E0(p);
}
