/* GAMECORE.XFF @ 0x127968 (28 B) - setGazeDirGazeIKWork
 * Evidence: ops lq lw sq
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
typedef unsigned int u_long128 __attribute__((mode(TI)));

void setGazeDirGazeIKWork(char *p, u_long128 *v) {
    char *g = F(p, char *, 0x110C);
    if (g)
        F(g, u_long128, 0x50) = *v;
}
