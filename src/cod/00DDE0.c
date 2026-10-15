/* asm/cod/00DDE0.s -> SceSifrpcCall.
 * cmd 4 of the SceSifrpcCall command family; template clone; R1
 * MATCHED (Session 8). */
extern int D_0013232C __attribute__((section(".data")));
extern int D_001471C0[];   /* .bss 0x001471C0, 0x40 bytes */
extern int D_00147200[];   /* .bss 0x00147200, 0x40 bytes */
extern int D_00147240[];   /* .bss 0x00147240, 0x40 bytes */

int SceSifrpcCall(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);

int func_0010DDE0(int a0, int a1, int a2) {
    int r;

    if (D_0013232C < 0)
        return 0;
    D_00147240[0] = a1;
    D_00147240[1] = a0;
    D_00147240[2] = a2;
    r = SceSifrpcCall((int)D_001471C0, 4, 0, (int)D_00147240, 0xC,
                      (int)D_00147200, 4, 0, 0);
    if (r < 0)
        return 0;
    return D_00147200[0];
}
