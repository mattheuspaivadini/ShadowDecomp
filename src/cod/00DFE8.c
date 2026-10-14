/* asm/cod/00DFE8.s -> func_00109980.
 * cmd 5; unsigned return keeps 0xFFFFFFFF as lui/ori (an int return folds it to addiu -1); R1 Phase A fix
 * MATCHED (Session 8). */
extern int D_0013232C __attribute__((section(".data")));
extern int D_001471C0[];   /* .bss 0x001471C0, 0x40 bytes -> %hi/%lo */
extern int D_00147200[];   /* .bss 0x00147200, 0x40 bytes -> %hi/%lo */

int func_00109980(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);

unsigned int func_0010DFE8(void) {
    if (D_0013232C < 0)
        return 0;
    if (func_00109980((int)D_001471C0, 5, 0, 0, 0, (int)D_00147200, 4, 0, 0) < 0)
        return 0xFFFFFFFF;
    return D_00147200[0];
}
