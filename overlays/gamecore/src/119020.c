/* GAMECORE.XFF @ 0x119020 (52 B) - SCRFuncSetGripDamage
 * Evidence: stores $ra, 0x0($sp), $f20, 0x8($sp); loads $f12, 0x180($v1), $a0, 0x4078($v0), $f20, 0x8($sp), $ra, 0x0($sp); relocs gcGlobalVar, gcGlobalVar+0x180; calls getSCRDataCtrlWork, j player_SetGripDamage; frame
 
 */
/* UNCONFIRMED: scales the grip damage by gcGlobalVar+0x180 and applies it to
 * the player object at +0x4078.
 */
extern char gcGlobalVar[];
char *getSCRDataCtrlWork(void);
void player_SetGripDamage(void *player, float damage);

void SCRFuncSetGripDamage(float damage) {
    char *work = getSCRDataCtrlWork();
    player_SetGripDamage(*(void **)(work + 0x4078),
                         damage * *(float *)(gcGlobalVar + 0x180));
}
