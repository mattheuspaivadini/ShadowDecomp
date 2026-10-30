/* GAMECORE.XFF @ 0x02E010 (20 B) - time_attack_end
 * Evidence: sw zero to gstatTimeAttackMode and gstatKaisouMode
 * UNCONFIRMED: none
 */
extern int gstatTimeAttackMode;
extern int gstatKaisouMode;

void time_attack_end(void) {
    gstatTimeAttackMode = 0;
    gstatKaisouMode = 0;
}
