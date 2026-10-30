/* GAMECORE.XFF @ 0x0E11A8 (12 B) - CAM_is_acting_view_cut_avoid_cntrl
 * Evidence: ops lw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
int CAM_is_acting_view_cut_avoid_cntrl(char *p) {
    return F(p, int, 0) != 0;
}
