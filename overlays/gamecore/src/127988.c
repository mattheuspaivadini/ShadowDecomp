/* GAMECORE.XFF @ 0x127988 (20 B) - setSubParamGazeIKWork
 * Evidence: ops lw sw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void setSubParamGazeIKWork(char *p, int v) {
    char *g = F(p, char *, 0x110C);
    if (g)
        F(g, int, 0xBC) = v;
}
