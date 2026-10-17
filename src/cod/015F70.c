/* asm/cod/015F70.s -> sceDbcDeleteSocket.
 * SCE libdbc; reply word read before SignalSema (Session 19)
 * MATCHED. */
extern int D_00133A28[];   /* .data 0x00133A28, 4 bytes -> lui/%lo */
extern int D_0014E900[];   /* .bss 0x0014E900, 0x50 bytes -> lui/%lo */
extern int D_0014EA00[];   /* .bss 0x0014EA00, 0xC0 bytes -> lui/%lo */
extern int D_00150DC0[];   /* .bss 0x00150DC0, 0x40 bytes -> lui/%lo */
extern char D_001386A0[];  /* error message -> lui/%lo */

int sceSifCallRpc(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);
void func_00116C58(int a0, ...);
int WaitSema(int a0);
int SignalSema(int a0);

int sceDbcDeleteSocket(int a0) {
    int r;

    if (D_00133A28[0] == 0)
        return 0;
    WaitSema(D_00150DC0[0]);
    D_0014EA00[0] = a0;
    r = sceSifCallRpc((int)D_0014E900, 0x80001302, 0, (int)D_0014EA00, 0x90,
                      (int)D_0014EA00, 0x90, 0, 0);
    if (r < 0) {
        func_00116C58((int)D_001386A0);
        SignalSema(D_00150DC0[0]);
        return 0;
    }
    r = D_0014EA00[1];
    SignalSema(D_00150DC0[0]);
    return r;
}
