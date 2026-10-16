/* asm/cod/015DD0.s -> SceSifrpcCall.
 * clone of matched 015A30 (modId 0x80001304 + p[1]=a0); wave3d (R1)
 * MATCHED (Session 8). */
int sceSifCallRpc(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);
void func_00116C58(int a0, ...);

extern int D_0014E900[];    /* .bss 0x0014E900, lui/%lo */
extern int D_0014EA00[];    /* .bss 0x0014EA00, lui/%lo */
extern char D_00138660[];   /* lui/%lo: the error message */

int sceDbcSetWorkAddr(int a0) {
    D_0014EA00[1] = a0;
    if (sceSifCallRpc((int)D_0014E900, 0x80001304, 0, (int)D_0014EA00, 0x90,
                      (int)D_0014EA00, 0x90, 0, 0) >= 0)
        return D_0014EA00[0];
    func_00116C58((int)D_00138660);
    return 0;
}
