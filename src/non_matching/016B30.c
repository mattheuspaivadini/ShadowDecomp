/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 39 [cc=29].
 * R3 famB: sceDbcReceiveData (lock + 0x90 payload + byte copy)
 * The original .s stays in the build (asm/cod/016B30.s); this C
 * draft (Session 8) is kept for the record. */
int SceSifrpcCall(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);
int func_00107020(int a0);
int func_00107000(int a0);
void func_00116C58(int a0, ...);

extern int D_0014E900[];    /* .bss 0x0014E900, lui/%lo */
extern int D_0014EA00[];    /* .bss 0x0014EA00, lui/%lo */
extern int D_00150DC0[];    /* lui/%lo: the DBC lock word */
extern char D_00138848[];   /* lui/%lo: the error message */

int sceDbcReceiveData(int a0, int a1, int *a2, char *a3) {
    int i;
    int n;

    func_00107020(D_00150DC0[0]);
    D_0014EA00[0] = a0;
    D_0014EA00[1] = a1;
    D_0014EA00[2] = *a2;
    if (SceSifrpcCall((int)D_0014E900, 0x8000131A, 0, (int)D_0014EA00, 0x90,
                      (int)D_0014EA00, 0x90, 0, 0) < 0) {
        func_00116C58((int)D_00138848);
        func_00107000(D_00150DC0[0]);
        return 0;
    }
    n = D_0014EA00[0x23];
    if (n >= 0) {
        *a2 = D_0014EA00[2];
        for (i = 0; i < D_0014EA00[2]; i++)
            a3[i] = ((char *)D_0014EA00)[0xC + i];
        n = D_0014EA00[0x23];
    }
    func_00107000(D_00150DC0[0]);
    return n;
}
