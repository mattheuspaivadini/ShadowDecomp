/* asm/cod/00E1B8.s -> func_00109980.
 * cmd 9; clone of 00E138 + unsigned-return fix; R1
 * MATCHED (Session 8). */
extern int D_0013232C __attribute__((section(".data")));
extern int D_001471C0[];   /* .bss 0x001471C0, 0x40 bytes */
extern int D_00147200[];   /* .bss 0x00147200, 0x40 bytes */
extern int D_00147240[];   /* .bss 0x00147240, 0x40 bytes */

int func_00109980(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);

unsigned int func_0010E1B8(int a0) {
    int r;

    if (D_0013232C < 0)
        return 0;
    D_00147240[0] = a0;
    r = func_00109980((int)D_001471C0, 9, 0, (int)D_00147240, 4,
                      (int)D_00147200, 4, 0, 0);
    if (r < 0)
        return 0xFFFFFFFF;
    return D_00147200[0];
}
