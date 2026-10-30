/* GAMECORE.XFF @ 0x1279D0 (20 B) - setExecGazeIKWork
 * Evidence: ops lw sw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void setExecGazeIKWork(char *p, int v) {
    char *g = F(p, char *, 0x110C);
    if (g)
        F(g, int, 0x30) = v;
}
