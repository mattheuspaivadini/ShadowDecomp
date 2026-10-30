/* GAMECORE.XFF @ 0x107A88 (16 B) - setPosGazeCtrlWork
 * Evidence: ops lq sq sw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
typedef unsigned int u_long128 __attribute__((mode(TI)));

void setPosGazeCtrlWork(char *p, u_long128 *v) {
    F(p, int, 0x30) = 0;
    F(p, u_long128, 0x20) = *v;
}
