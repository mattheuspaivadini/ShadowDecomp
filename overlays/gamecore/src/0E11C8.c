/* GAMECORE.XFF @ 0x0E11C8 (24 B) - CAM_reset_obstacle_avoid_cntrl
 * Evidence: ops sw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void CAM_reset_obstacle_avoid_cntrl(char *p) {
    F(p, int, 0) = 0;
    F(p, int, 4) = 0;
    F(p, int, 8) = 0;
    F(p, int, 0xC) = 0;
    F(p, int, 0x10) = 0;
}
