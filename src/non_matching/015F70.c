/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 5 [cc=29].
 * R3 famA: Dbc one-shot guard + lock/unlock
 * The original .s stays in the build (asm/cod/015F70.s); this C
 * draft (Session 8) is kept for the record. */
extern int D_00133A28[];   /* .data 0x00133A28, 4 bytes -> lui/%lo */
extern int D_0014E900[];   /* .bss 0x0014E900, 0x50 bytes -> lui/%lo */
extern int D_0014EA00[];   /* .bss 0x0014EA00, 0xC0 bytes -> lui/%lo */
extern int D_00150DC0[];   /* .bss 0x00150DC0, 0x40 bytes -> lui/%lo */
extern char D_001386A0[];  /* error message -> lui/%lo */

int func_00109980(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);
void func_00116C58(int a0, ...);
int func_00107020(int a0);
int func_00107000(int a0);

int sceDbcDeleteSocket(int a0) {
    int r;

    if (D_00133A28[0] == 0)
        return 0;
    func_00107020(D_00150DC0[0]);
    D_0014EA00[0] = a0;
    r = func_00109980((int)D_0014E900, 0x80001302, 0, (int)D_0014EA00, 0x90,
                      (int)D_0014EA00, 0x90, 0, 0);
    if (r < 0) {
        func_00116C58((int)D_001386A0);
        func_00107000(D_00150DC0[0]);
        return 0;
    }
    func_00107000(D_00150DC0[0]);
    return D_0014EA00[1];
}
