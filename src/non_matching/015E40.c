/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 35 [cc=29].
 * R3 famB: sceDbcCreateSocket
 * The original .s stays in the build (asm/cod/015E40.s); this C
 * draft (Session 8) is kept for the record. */
int SceSifrpcCall(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);
int func_00107020(int a0);
int func_00107000(int a0);
void func_00116C58(int a0, ...);

extern int D_0014E900[];    /* .bss 0x0014E900, lui/%lo */
extern int D_0014EA00[];    /* .bss 0x0014EA00, lui/%lo */
extern int D_00150DC0[];    /* lui/%lo: the DBC lock word */
extern int D_00133A28[];    /* lui/%lo: the module-ready flag */
extern char D_00138680[];   /* lui/%lo: the error message */

int sceDbcCreateSocket(int *a0, int a1, int a2) {
    int i;
    int r;

    if (D_00133A28[0] == 0)
        return 0;
    func_00107020(D_00150DC0[0]);
    D_0014EA00[0] = a0[0];
    D_0014EA00[10] = a1;
    D_0014EA00[11] = a2;
    D_0014EA00[1] = a0[1];
    D_0014EA00[2] = a0[2];
    D_0014EA00[3] = a0[3];
    D_0014EA00[4] = a0[4];
    for (i = 0; i < 0x10; i++)
        ((char *)D_0014EA00)[0x14 + i] = ((char *)a0)[0x14 + i];
    if (SceSifrpcCall((int)D_0014E900, 0x80001301, 0, (int)D_0014EA00, 0x90,
                      (int)D_0014EA00, 0x90, 0, 0) < 0) {
        func_00116C58((int)D_00138680);
        func_00107000(D_00150DC0[0]);
        return 0;
    }
    r = D_0014EA00[9];
    func_00107000(D_00150DC0[0]);
    return r;
}
