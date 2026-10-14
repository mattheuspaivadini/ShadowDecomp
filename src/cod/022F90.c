/* asm/cod/022F90.s -> func_00108FF8.
 * 7-arg func_00109C58 materialisation + tail (func_001230B0 idiom); wave3d (R1)
 * MATCHED (Session 8). */
int func_00108FF8(int x);
int func_00106ED0(void);
int func_00109BC0(int a0, int a1);
int func_00109C58(int a0, int a1, int a2, int a3, int a4, int a5, int a6);
void func_0010A070(int *ctx);
void func_00122EA8(void);   /* the callback stored by the func_00109C58 call */

extern int D_00169F10[];   /* lui/%lo */
extern int D_00169F58[];   /* lui/%lo */
extern int D_00168F00[];   /* lui/%lo */

void func_00122F90(void) {
    func_00108FF8(0);
    func_00109BC0((int)D_00169F58, func_00106ED0());
    func_00109C58((int)D_00169F10, 0x80001101, (int)func_00122EA8,
                  (int)D_00168F00, 0, 0, (int)D_00169F58);
    func_0010A070(D_00169F58);
}
