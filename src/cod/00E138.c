/* asm/cod/00E138.s -> SceSifrpcCall.
 * cmd 8; clone of 00DE60 + unsigned-return fix; R1
 * MATCHED (Session 8). */
extern int D_0013232C __attribute__((section(".data")));
extern int D_001471C0[];   /* .bss 0x001471C0, 0x40 bytes */
extern int D_00147200[];   /* .bss 0x00147200, 0x40 bytes */
extern int D_00147240[];   /* .bss 0x00147240, 0x40 bytes */

int sceSifCallRpc(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);

unsigned int sceSifQueryBlockTopAddress(int a0) {
    int r;

    if (D_0013232C < 0)
        return 0;
    D_00147240[0] = a0;
    r = sceSifCallRpc((int)D_001471C0, 8, 0, (int)D_00147240, 4,
                      (int)D_00147200, 4, 0, 0);
    if (r < 0)
        return 0xFFFFFFFF;
    return D_00147200[0];
}
