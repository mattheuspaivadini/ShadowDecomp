/* GAMECORE.XFF @ 0x0E0960 (24 B) - CAM_get_ground_contact_obj
 * Evidence: ops lw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
int CAM_get_ground_contact_obj(char *p) {
    int o = F(p, int, 0x2C8);
    if (o)
        return o;
    return F(p, int, 0);
}
