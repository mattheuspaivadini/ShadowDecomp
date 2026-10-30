/* GAMECORE.XFF @ 0x0E11B8 (12 B) - CAM_set_param_view_cut_avoid_cntrl
 * Evidence: ops swc1
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void CAM_set_param_view_cut_avoid_cntrl(char *p, float a, float b) {
    F(p, float, 0x94) = a;
    F(p, float, 0x98) = b;
}
