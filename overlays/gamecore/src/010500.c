/* GAMECORE.XFF @ 0x010500 (32 B) - bossStatChkDeadBoss
 * Evidence: jal _gameFlagChk([a0+0x18]); sltiu v0,v0,1
 * UNCONFIRMED: none
 */
int _gameFlagChk(int f);

int bossStatChkDeadBoss(int *boss) {
    return !_gameFlagChk(boss[6]);
}
