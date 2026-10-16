/* asm/cod/0164A8.s -> SceSifrpcCall.
 * cmd 0x8000131D + intermediate-result shape
 * MATCHED (Session 8). */
extern int D_0014E900[];   /* .bss 0x0014E900, 0x50 bytes -> lui/%lo */
extern int D_0014EA00[];   /* .bss 0x0014EA00, 0xC0 bytes -> lui/%lo */
extern int D_00150DC0[];   /* .bss 0x00150DC0, 0x40 bytes -> lui/%lo */
extern char D_00138720[];  /* error message -> lui/%lo */

int sceSifCallRpc(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);
void func_00116C58(int a0, ...);
int WaitSema(int a0);
int SignalSema(int a0);

int sceDbcSearchPortSpecific(int *a0) {
    int r;
    int v;

    WaitSema(D_00150DC0[0]);
    D_0014EA00[2] = 2;
    D_0014EA00[4] = a0[2];
    D_0014EA00[5] = a0[3];
    r = sceSifCallRpc((int)D_0014E900, 0x8000131D, 0, (int)D_0014EA00, 0x90,
                      (int)D_0014EA00, 0x90, 0, 0);
    if (r < 0) {
        func_00116C58((int)D_00138720);
        SignalSema(D_00150DC0[0]);
        return -1;
    }
    v = D_0014EA00[1];
    SignalSema(D_00150DC0[0]);
    return v;
}
