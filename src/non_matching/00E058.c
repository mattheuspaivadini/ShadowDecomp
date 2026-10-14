/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 4 [cc=29, default].
 * same family, cmd 6.
 * The original .s stays in the build (asm/cod/00E058.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/00E058.s -> func_0010E058 @ 0x0010E058 (0x70 bytes, 28 insns)
 *
 * Command 6 of the D_001471C0/D_00147200 transfer block - identical to
 * func_0010DFE8 except for the command byte:
 *   if (D_0013232C < 0) return 0;
 *   r = func_00109980(&D_001471C0, 6, 0, 0, 0, &D_00147200, 4, 0, 0);
 *   if (r < 0) return 0xFFFFFFFF;                ; lui/ori (2.9 materialisation)
 *   return D_00147200[0];                        ; lw in the bgezl delay slot
 * MATCH GUESS: cc=29 (func_00109980 9-arg family + lui/ori 0xFFFFFFFF)
 */
extern int D_0013232C __attribute__((section(".data")));
extern int D_001471C0[];   /* .bss 0x001471C0, 0x40 bytes */
extern int D_00147200[];   /* .bss 0x00147200, 0x40 bytes */

int func_00109980(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);

int func_0010E058(void) {
    int r;

    if (D_0013232C < 0)
        return 0;
    r = func_00109980((int)D_001471C0, 6, 0, 0, 0, (int)D_00147200, 4, 0, 0);
    if (r < 0)
        return 0xFFFFFFFF;
    return D_00147200[0];
}
