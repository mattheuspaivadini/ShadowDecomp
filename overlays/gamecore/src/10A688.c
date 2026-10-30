/* GAMECORE.XFF @ 0x10A688 (28 B) - setAllowMaxSpeedHorseCtrlWork
 * Evidence: ops lw lwc1 swc1
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void setAllowMaxSpeedHorseCtrlWork(char *p, float v) {
    if (*F(p, float *, 0x78) < v)
        F(p, float, 0x40) = v;
}
