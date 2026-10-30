/* GAMECORE.XFF @ 0x11D030 (44 B) - SCRConditionDamagedPlayer
 * Evidence: stores $ra, 0x0($sp); loads $a0, 0x4078($v0), $v0, 0x0($v0), $ra, 0x0($sp); calls getSCRDataCtrlWork, GetDamageClass; frame
 
 */
/* UNCONFIRMED: GetDamageClass returns a block whose first word is the damage
 * state.
 */
char *getSCRDataCtrlWork(void);
void *GetDamageClass(void *player);

int SCRConditionDamagedPlayer(void) {
    char *work = getSCRDataCtrlWork();
    return *(int *)GetDamageClass(*(void **)(work + 0x4078)) != 0;
}
