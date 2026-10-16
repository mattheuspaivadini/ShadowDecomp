/* asm/cod/00E0C8.s -> SceSifrpcCall.
 * cmd 7; same unsigned-return fix; R1 Phase A
 * MATCHED (Session 8). */
extern int D_0013232C __attribute__((section(".data")));
extern int D_001471C0[];   /* .bss 0x001471C0, 0x40 bytes -> %hi/%lo */
extern int D_00147200[];   /* .bss 0x00147200, 0x40 bytes -> %hi/%lo */

int sceSifCallRpc(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);

unsigned int sceSifQueryTotalFreeMemSize(void) {
    if (D_0013232C < 0)
        return 0;
    if (sceSifCallRpc((int)D_001471C0, 7, 0, 0, 0, (int)D_00147200, 4, 0, 0) < 0)
        return 0xFFFFFFFF;
    return D_00147200[0];
}
