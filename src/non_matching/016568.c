/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 56 [cc=29].
 * R3 famC: two indexed byte-copy loops; r reload in the bgezl shadow
 * The original .s stays in the build (asm/cod/016568.s); this C
 * draft (Session 8) is kept for the record. */
extern int D_00150DC0[];    /* .bss 0x00150DC0 (the lock handle) -> lui/%lo */
extern int D_0014E900[];    /* .bss 0x0014E900 (request) -> lui/%lo */
extern int D_0014EA00[];    /* .bss 0x0014EA00, 0xC0 bytes -> lui/%lo */
extern char D_00138748[];   /* .rodata: the error message -> lui/%lo */

int SceSifrpcCall(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);
void func_00107020(int a0);
void func_00107000(int a0);
void func_00116C58(int a0);

int sceDbcSRData(int a0, int a1, int *a2, unsigned char *a3, int *a4,
                 unsigned char *a5) {
    int i;
    int r;

    func_00107020(D_00150DC0[0]);
    D_0014EA00[0] = a0;
    D_0014EA00[1] = a1;
    D_0014EA00[2] = *a2;
    D_0014EA00[3] = *a4;
    for (i = 0; i < *a2; i++)
        ((unsigned char *)D_0014EA00)[0x10 + i] = a3[i];
    r = SceSifrpcCall((int)D_0014E900, 0x80001318, 0, (int)D_0014EA00, 0x90,
                      (int)D_0014EA00, 0x90, 0, 0);
    if (r < 0) {
        func_00116C58((int)D_00138748);
        func_00107000(D_00150DC0[0]);
        return 0;
    }
    r = D_0014EA00[0x44];
    if (r >= 0) {
        *a2 = D_0014EA00[2];
        *a4 = D_0014EA00[3];
        for (i = 0; i < D_0014EA00[3]; i++)
            a5[i] = ((unsigned char *)D_0014EA00)[0x90 + i];
        r = D_0014EA00[0x44];
    }
    func_00107000(D_00150DC0[0]);
    return r;
}
