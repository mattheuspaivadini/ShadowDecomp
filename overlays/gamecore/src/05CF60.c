/* GAMECORE.XFF @ 0x05CF60 (52 B) - SCRConditionHorseForceStandby
 * Evidence: `jal gameflowGetJumpSekiban`, the result kept in `$s0` across
 * `jal gameflowSetJumpSekiban(0)`, then `$v0 = $s0`.
 * UNCONFIRMED: the callee prototypes and the "sekiban" meaning.
 
 */
int gameflowGetJumpSekiban(void);
void gameflowSetJumpSekiban(int sekiban);

int SCRConditionHorseForceStandby(void) {
    int sekiban = gameflowGetJumpSekiban();

    gameflowSetJumpSekiban(0);
    return sekiban;
}
