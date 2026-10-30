/* GAMECORE.XFF @ 0x112EB0 (28 B) - setRotParamWormCtrlWork
 * Evidence: ops swc1
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void setRotParamWormCtrlWork(char *p, float a, float b) {
    F(p, float, 0x6C) = a;
    F(p, float, 0x70) = b * 0.017453293f;
}
