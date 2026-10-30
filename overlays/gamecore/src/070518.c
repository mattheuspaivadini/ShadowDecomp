/* GAMECORE.XFF @ 0x070518 (12 B) - is_doing_nico_sight_on
 * Evidence: lw [a0]; sltu v0,zero,v0
 * UNCONFIRMED: none
 */
int is_doing_nico_sight_on(int *p) {
    return *p != 0;
}
