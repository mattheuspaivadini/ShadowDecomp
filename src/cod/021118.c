/* asm/cod/021118.s -> func_00106FF0.
 * session9 R1 w25b wave
 * MATCHED (Session 8). */
struct R021118 {
    int  field0;        /* 0x00 */
    int  field4;        /* 0x04 */
    char rest[0x1C];    /* to 0x24 */
};

extern struct R021118 D_00163CC8[];
extern int D_00163CC0[];
int DeleteSema(int a0);
int sceDbcDeleteSocket(int id);

int _sceMcCoreEnd(void) {
    int i;
    int v;

    v = D_00163CC0[0];
    if (v >= 0)
        DeleteSema(v);
    for (i = 0; i < 2; i++) {
        if (D_00163CC8[i].field0 != 0) {
            sceDbcDeleteSocket(D_00163CC8[i].field4);
            D_00163CC8[i].field0 = 0;
        }
    }
    return 1;
}
