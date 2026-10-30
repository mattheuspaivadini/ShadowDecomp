/* GAMECORE.XFF @ 0x1279B8 (20 B) - setExecRootQuatGazeIKWork
 * Evidence: ops lw sw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void setExecRootQuatGazeIKWork(char *p, int v) {
    char *g = F(p, char *, 0x110C);
    if (g)
        F(g, int, 0xB0) = v;
}
