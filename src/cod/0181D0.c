/* asm/cod/0181D0.s -> func_00109980.
 * func_001178A8 guard + double mirror read; famA (R3)
 * MATCHED (Session 8). */
extern char D_001355C0[];   /* request struct -> lui/%lo */
extern char D_00134C40[];   /* 8-byte reply buffer -> lui/%lo */
extern int D_00133A6C[];    /* handle word -> lui/%lo */

int func_00109980(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);
int func_001178A8(int a0);
int func_00107000(int a0);

int func_001181D0(int *a0) {
    int r;

    if (func_001178A8(0x21) == 0)
        return 0;
    r = func_00109980((int)D_001355C0, 0x21, 0, 0, 0, (int)D_00134C40, 8, 0, 0);
    if (r < 0) {
        func_00107000(D_00133A6C[0]);
        return 0;
    }
    *a0 = *(int *)((unsigned int)((int)D_00134C40 + 4) | 0x20000000);
    r = *(int *)((unsigned int)D_00134C40 | 0x20000000);
    func_00107000(D_00133A6C[0]);
    return r;
}
