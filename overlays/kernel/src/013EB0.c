/* KERNEL.XFF @ 0x013EB0 (928 B) - iosDumpVIF1Status  [MATCHED, -G0 -fno-strict-aliasing]
 * One-shot: no permutation needed. Evidence: argument-free VIF1 diagnostic dump. `lw` of 0x10003C00
 * (VIF1_STAT) into a callee-saved register that stays live across all 21
 * LoaderSysPrintf calls; every printed field is `(stat >> n) & 1` (the image
 * folds index*4 into `srl n-2 / andi 4`, so the source table index is
 * `(stat >> n) & 1`).  The five local table copies are aggregate local
 * initialisers: the .rodata templates at 0x1478 (2 ptrs), 0x14C0 (4 ptrs),
 * 0x14F0 / 0x1518 / 0x1540 (2 ptrs each) are copied onto the stack with
 * ldl/ldr+sdl/sdr (4-byte-pointer parenthesisation), and the copies sit in
 * the block *after* the first banner call, so the arrays are declared after
 * it.  Then: MARK (0x10003C30) and five 3/4-word register blocks - VIF1
 * ROW0..3 = 0x3D00..0x3D30, COL0..3 = 0x3D40..0x3D70, CYCLE/MASK/MODE =
 * 0x3C40/0x3C70/0x3C50, ITOP/ITOPS/BASE/OFST = 0x3CD0/0x3C90/0x3CA0/0x3CB0,
 * TOP/TOPS/NUM/CODE = 0x3CE0/0x3CC0/0x3C60/0x3C80 - each read through a
 * volatile pointer, matching the .rodata format strings.
 * UNCONFIRMED: table/string contents are referenced by image labels only.
 */

typedef unsigned int u32;

extern int LoaderSysPrintf(const char *fmt, ...);

extern char D_kernel_rodata_1430[];
extern char D_kernel_rodata_1468[];
extern char D_kernel_rodata_1470[];
extern char D_kernel_rodata_1480[];
extern char D_kernel_rodata_1490[];
extern char D_kernel_rodata_14A0[];
extern char D_kernel_rodata_14B0[];
extern char D_kernel_rodata_14D0[];
extern char D_kernel_rodata_14E0[];
extern char D_kernel_rodata_14F8[];
extern char D_kernel_rodata_1508[];
extern char D_kernel_rodata_1520[];
extern char D_kernel_rodata_1530[];
extern char D_kernel_rodata_1548[];
extern char D_kernel_rodata_1560[];
extern char D_kernel_rodata_1578[];
extern char D_kernel_rodata_1590[];
extern char D_kernel_rodata_15A8[];
extern char D_kernel_rodata_15C0[];
extern char D_kernel_rodata_15D8[];
extern char D_kernel_rodata_15F0[];
extern char D_kernel_rodata_1608[];
extern char D_kernel_rodata_1620[];
extern char D_kernel_rodata_1638[];
extern char D_kernel_rodata_1650[];
extern char D_kernel_rodata_1668[];
extern char D_kernel_rodata_1688[];
extern char D_kernel_rodata_16A8[];
extern char D_kernel_rodata_16C0[];
extern char D_kernel_rodata_1720[];
extern char D_kernel_rodata_1780[];
extern char D_kernel_rodata_17C8[];
extern char D_kernel_rodata_1828[];

void iosDumpVIF1Status(void) {
    LoaderSysPrintf(D_kernel_rodata_1430);
    {
        u32 stat = *(volatile u32 *)0x10003C00;
        char *onoff[] = { D_kernel_rodata_1468, D_kernel_rodata_1470 };
        char *status[] = { D_kernel_rodata_1480, D_kernel_rodata_1490,
                           D_kernel_rodata_14A0, D_kernel_rodata_14B0 };
        char *vurun[] = { D_kernel_rodata_14D0, D_kernel_rodata_14E0 };
        char *gifwait[] = { D_kernel_rodata_14F8, D_kernel_rodata_1508 };
        char *dir[] = { D_kernel_rodata_1520, D_kernel_rodata_1530 };

        LoaderSysPrintf(D_kernel_rodata_1548, status[stat & 3]);
        LoaderSysPrintf(D_kernel_rodata_1560, vurun[(stat >> 2) & 1]);
        LoaderSysPrintf(D_kernel_rodata_1578, gifwait[(stat >> 3) & 1]);
        LoaderSysPrintf(D_kernel_rodata_1590, onoff[(stat >> 6) & 1]);
        LoaderSysPrintf(D_kernel_rodata_15A8, (stat >> 7) & 1);
        LoaderSysPrintf(D_kernel_rodata_15C0, onoff[(stat >> 8) & 1]);
        LoaderSysPrintf(D_kernel_rodata_15D8, onoff[(stat >> 9) & 1]);
        LoaderSysPrintf(D_kernel_rodata_15F0, onoff[(stat >> 10) & 1]);
        LoaderSysPrintf(D_kernel_rodata_1608, onoff[(stat >> 11) & 1]);
        LoaderSysPrintf(D_kernel_rodata_1620, onoff[(stat >> 12) & 1]);
        LoaderSysPrintf(D_kernel_rodata_1638, onoff[(stat >> 13) & 1]);
        LoaderSysPrintf(D_kernel_rodata_1650, dir[(stat >> 23) & 1]);
        LoaderSysPrintf(D_kernel_rodata_1668, (stat >> 24) & 0x1F, (stat >> 24) & 0x1F);
    }
    LoaderSysPrintf(D_kernel_rodata_1688);
    LoaderSysPrintf(D_kernel_rodata_16A8, *(volatile u32 *)0x10003C30);
    LoaderSysPrintf(D_kernel_rodata_16C0, *(volatile u32 *)0x10003D00,
                    *(volatile u32 *)0x10003D10, *(volatile u32 *)0x10003D20,
                    *(volatile u32 *)0x10003D30);
    LoaderSysPrintf(D_kernel_rodata_1720, *(volatile u32 *)0x10003D40,
                    *(volatile u32 *)0x10003D50, *(volatile u32 *)0x10003D60,
                    *(volatile u32 *)0x10003D70);
    LoaderSysPrintf(D_kernel_rodata_1780, *(volatile u32 *)0x10003C40,
                    *(volatile u32 *)0x10003C70, *(volatile u32 *)0x10003C50);
    LoaderSysPrintf(D_kernel_rodata_17C8, *(volatile u32 *)0x10003CD0,
                    *(volatile u32 *)0x10003C90, *(volatile u32 *)0x10003CA0,
                    *(volatile u32 *)0x10003CB0);
    LoaderSysPrintf(D_kernel_rodata_1828, *(volatile u32 *)0x10003CE0,
                    *(volatile u32 *)0x10003CC0, *(volatile u32 *)0x10003C60,
                    *(volatile u32 *)0x10003C80);
}
