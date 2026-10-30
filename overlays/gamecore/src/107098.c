/* GAMECORE.XFF @ 0x107098 (24 B) - setAllowMaxSpeedFastLegCtrlWork
 * Evidence: ops lwc1 swc1
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void setAllowMaxSpeedFastLegCtrlWork(char *p, float v) {
    if (F(p, float, 0x7C) < v)
        F(p, float, 0x50) = v;
}
