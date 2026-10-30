/* GAMECORE.XFF @ 0x1279A0 (20 B) - setGazeModeGazeIKWork
 * Evidence: ops lw sw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void setGazeModeGazeIKWork(char *p, int v) {
    char *g = F(p, char *, 0x110C);
    if (g)
        F(g, int, 0x60) = v;
}
