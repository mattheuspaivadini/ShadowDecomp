/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 35 [cc=29].
 * R3 famC: error-tail cross-jump + base re-materialisation
 * The original .s stays in the build (asm/cod/016828.s); this C
 * draft (Session 8) is kept for the record. */
extern int D_00150DC0[];    /* .bss 0x00150DC0 (the lock handle) -> lui/%lo */
extern int D_00150B80[];    /* .bss 0x00150B80, 0x180 bytes -> lui/%lo */
extern int D_0014E978[];    /* .bss 0x0014E978, 0x88 bytes -> lui/%lo */
extern int D_00133A2C[];    /* .bss 0x00133A2C (the 0/1 slot counter) -> lui/%lo */
extern char D_00138788[];   /* .rodata: the size error message -> lui/%lo */
extern char D_001387B8[];   /* .rodata: the first error message -> lui/%lo */
extern char D_001387D8[];   /* .rodata: the second error message -> lui/%lo */

int func_00109980(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);
int func_00109B80(int a0);
void func_00107020(int a0);
void func_00107000(int a0);
void func_00116C58(int a0, ...);

int sceDbcSendData2(int a0, int a1, int *a2, unsigned char *a3) {
    int i;
    int r;

    if (*a2 >= 0x81) {
        func_00116C58((int)D_00138788, *a2);
        return 0;
    }
    func_00107020(D_00150DC0[0]);
    D_00133A2C[0] = D_00133A2C[0] + 1;
    if (D_00133A2C[0] >= 2)
        D_00133A2C[0] = 0;
    *(int *)((char *)D_00150B80 + D_00133A2C[0] * 0xC0 + 0x0) = a0;
    *(int *)((char *)D_00150B80 + D_00133A2C[0] * 0xC0 + 0x4) = a1;
    *(int *)((char *)D_00150B80 + D_00133A2C[0] * 0xC0 + 0x8) = *a2;
    for (i = 0; i < *a2; i++)
        ((unsigned char *)((char *)D_00150B80 + D_00133A2C[0] * 0xC0))[0xC + i] =
            a3[i];
    if (func_00109B80((int)D_0014E978 + D_00133A2C[0] * 0x28) == 1) {
        func_00116C58((int)D_001387B8);
        func_00107000(D_00150DC0[0]);
        return 0;
    }
    r = func_00109980((int)D_0014E978 + D_00133A2C[0] * 0x28, D_00133A2C[0], 1,
                      (int)((char *)D_00150B80 + D_00133A2C[0] * 0xC0), 0x90,
                      (int)((char *)D_00150B80 + D_00133A2C[0] * 0xC0), 0x90, 0, 0);
    if (r < 0) {
        func_00116C58((int)D_001387D8);
        func_00107000(D_00150DC0[0]);
        return 0;
    }
    func_00107000(D_00150DC0[0]);
    return 1;
}
