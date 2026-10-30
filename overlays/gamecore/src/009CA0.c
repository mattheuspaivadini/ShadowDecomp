/* GAMECORE.XFF @ 0x009CA0 (32 B) - GAMEUTIL_is_boss_booting
 * Evidence: calls bossStatBootChk() and returns `bossStatBootChk() > 0`
 * via `slt $v0, $zero, $v0`.
 */
int bossStatBootChk(void);

int GAMEUTIL_is_boss_booting(void) {
    return bossStatBootChk() > 0;
}
