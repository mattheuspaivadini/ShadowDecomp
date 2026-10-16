/* asm/cod/003CB8.s -> func_00105948.
 * clean; w45a_1 (R2)
 * MATCHED (Session 8). */
extern char D_00136B00[];   /* lui/%lo */
extern char D_00136B10[];   /* lui/%lo */
extern char D_0013A018[];   /* lui/%lo */
extern char D_0013A020[];   /* lui/%lo */
extern char D_0013A028[];   /* lui/%lo */

void PutString(int a0, int a1, ...);
void PutStringS(int a0, int a1, ...);
int  sceSifLoadModule(int a0, int a1, int a2);

int LoaderSysLoadIopModule(int a0, int a1, int a2) {
    int r;

    PutString(0x4080FF00, (int)D_00136B00, a2);
    PutString(0x80C0FF00, (int)D_0013A018, a0);
    PutStringS(0x4080FF00, (int)D_0013A020);
    r = sceSifLoadModule(a0, a1, a2);
    if (r < 0) {
        PutStringS(0xFF804000, (int)D_00136B10, a0, r);
        return -1;
    }
    PutStringS(0x4080FF00, (int)D_0013A028);
    return 0;
}
