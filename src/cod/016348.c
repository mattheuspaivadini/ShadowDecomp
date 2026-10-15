/* asm/cod/016348.s -> SceSifrpcCall.
 * sceDbcResetSocket: cmd 0x80001316 + intermediate-result shape
 * MATCHED (Session 8). */
extern int D_0014E900[];   /* .bss 0x0014E900, 0x50 bytes -> lui/%lo */
extern int D_0014EA00[];   /* .bss 0x0014EA00, 0xC0 bytes -> lui/%lo */
extern int D_00150DC0[];   /* .bss 0x00150DC0, 0x40 bytes -> lui/%lo */
extern char D_00138700[];  /* error message -> lui/%lo */

int SceSifrpcCall(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);
void func_00116C58(int a0, ...);
int func_00107020(int a0);
int func_00107000(int a0);

int sceDbcResetSocket(int a0) {
    int r;
    int v;

    func_00107020(D_00150DC0[0]);
    D_0014EA00[0] = a0;
    r = SceSifrpcCall((int)D_0014E900, 0x80001316, 0, (int)D_0014EA00, 0x90,
                      (int)D_0014EA00, 0x90, 0, 0);
    if (r < 0) {
        func_00116C58((int)D_00138700);
        func_00107000(D_00150DC0[0]);
        return 0;
    }
    v = D_0014EA00[1];
    func_00107000(D_00150DC0[0]);
    return v;
}
