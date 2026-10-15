/* asm/cod/0164A8.s -> func_00109980.
 * cmd 0x8000131D + intermediate-result shape
 * MATCHED (Session 8). */
extern int D_0014E900[];   /* .bss 0x0014E900, 0x50 bytes -> lui/%lo */
extern int D_0014EA00[];   /* .bss 0x0014EA00, 0xC0 bytes -> lui/%lo */
extern int D_00150DC0[];   /* .bss 0x00150DC0, 0x40 bytes -> lui/%lo */
extern char D_00138720[];  /* error message -> lui/%lo */

int func_00109980(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);
void func_00116C58(int a0, ...);
int func_00107020(int a0);
int func_00107000(int a0);

int func_001164A8(int *a0) {
    int r;
    int v;

    func_00107020(D_00150DC0[0]);
    D_0014EA00[2] = 2;
    D_0014EA00[4] = a0[2];
    D_0014EA00[5] = a0[3];
    r = func_00109980((int)D_0014E900, 0x8000131D, 0, (int)D_0014EA00, 0x90,
                      (int)D_0014EA00, 0x90, 0, 0);
    if (r < 0) {
        func_00116C58((int)D_00138720);
        func_00107000(D_00150DC0[0]);
        return -1;
    }
    v = D_0014EA00[1];
    func_00107000(D_00150DC0[0]);
    return v;
}
