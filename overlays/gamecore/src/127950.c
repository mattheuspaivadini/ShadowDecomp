/* GAMECORE.XFF @ 0x127950 (20 B) - setGoingAngleGazeIKWork
 * Evidence: ops lw swc1
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void setGoingAngleGazeIKWork(char *p, float v) {
    char *g = F(p, char *, 0x110C);
    if (g)
        F(g, float, 0x40) = v;
}
