/* asm/cod/022F90.s -> func_00108FF8.
 * 7-arg func_00109C58 materialisation + tail (func_001230B0 idiom); wave3d (R1)
 * MATCHED (Session 8). */
int sceSifInitRpc(int x);
int GetThreadId(void);
int sceSifSetRpcQueue(int a0, int a1);
int sceSifRegisterRpc(int a0, int a1, int a2, int a3, int a4, int a5, int a6);
void sceSifRpcLoop(int *ctx);
void func_00122EA8(void);   /* the callback stored by the func_00109C58 call */

extern int D_00169F10[];   /* lui/%lo */
extern int D_00169F58[];   /* lui/%lo */
extern int D_00168F00[];   /* lui/%lo */

void func_00122F90(void) {
    sceSifInitRpc(0);
    sceSifSetRpcQueue((int)D_00169F58, GetThreadId());
    sceSifRegisterRpc((int)D_00169F10, 0x80001101, (int)func_00122EA8,
                  (int)D_00168F00, 0, 0, (int)D_00169F58);
    sceSifRpcLoop(D_00169F58);
}
