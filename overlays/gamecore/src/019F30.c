/* GAMECORE.XFF @ 0x019F30 (60 B) - gStatInitNotOmakeInit
 * Evidence: four calls (gameFlagInit, bossStatInit, backStageInit,
 * time_attack_init_gstat_adrs) then a tail `j .text+0x18DC8` with `$a0 = 0`,
 * `$a1 = 1`.
 * UNCONFIRMED: the tail callee's name.
 
 */
void gameFlagInit(void);
void bossStatInit(void);
void backStageInit(void);
void time_attack_init_gstat_adrs(void);
void func_018DC8(int a0, int a1);

void gStatInitNotOmakeInit(void) {
    gameFlagInit();
    bossStatInit();
    backStageInit();
    time_attack_init_gstat_adrs();
    func_018DC8(0, 1);
}
