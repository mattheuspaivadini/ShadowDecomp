/* asm/cod/003D88.s -> func_00105948.
 * clean; w45a_1 (R2)
 * MATCHED (Session 8). */
extern char D_00136B48[];   /* lui/%lo */
extern char D_00136B58[];   /* lui/%lo */
extern char D_0013A018[];   /* lui/%lo */
extern char D_0013A020[];   /* lui/%lo */
extern char D_0013A028[];   /* lui/%lo */
extern char D_0013A030[];   /* lui/%lo */

void PutString(int a0, int a1, ...);
void PutStringS(int a0, int a1, ...);
int  sceSifSearchModuleByName(int a0);
int  sceSifStopModule(int a0, int a1, int a2, int *a3);
int  sceSifUnloadModule(int a0);

int LoaderSysUnloadIopModuleByName(int a0, int a1, int a2, int *a3) {
    int h;
    int v;
    int buf;

    PutString(0x4080FF00, (int)D_00136B48, a2);
    PutString(0x80C0FF00, (int)D_0013A018, a0);
    PutStringS(0x4080FF00, (int)D_0013A020);
    h = sceSifSearchModuleByName(a0);
    if (h >= 0) {
        v = sceSifStopModule(h, 1, (int)D_0013A030, a3 != 0 ? a3 : &buf);
        if (v >= 0)
            v = sceSifUnloadModule(h);
    } else {
        v = h;
    }
    if (v < 0) {
        PutStringS(0xFF804000, (int)D_00136B58, a0, v);
        return -1;
    }
    PutStringS(0x4080FF00, (int)D_0013A028);
    return v;
}
