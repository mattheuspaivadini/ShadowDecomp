/* GAMECORE.XFF @ 0x0E3038 (32 B) - change_camera_target
 * Evidence: ops sw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
int change_camera_target(char *p, int t) {
    if (t) {
        F(p, int, 0x1C) = t;
        return 1;
    }
    return 0;
}
