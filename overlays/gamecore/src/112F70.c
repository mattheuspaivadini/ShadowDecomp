/* GAMECORE.XFF @ 0x112F70 (12 B) - setAcceleParamWormCtrlWork
 * Evidence: ops swc1
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void setAcceleParamWormCtrlWork(char *p, float a, float b) {
    F(p, float, 0x5C) = a;
    F(p, float, 0x60) = b;
}
