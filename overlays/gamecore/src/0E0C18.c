/* GAMECORE.XFF @ 0x0E0C18 (12 B) - CAM_is_visible_now_target_visibility
 * Evidence: ops lw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
int CAM_is_visible_now_target_visibility(char *p) {
    return F(p, int, 0x44) == 0;
}
