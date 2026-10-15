/* asm/cod/00E8A0.s -> func_0010E238.
 * family sibling of matched 00E810/00E940 (0xFC copy + cmd 9); famA (R3)
 * MATCHED (Session 8). */
extern int D_00147388[];   /* .bss: transport base (lui/%lo) */
extern int D_00147580[];   /* .bss transfer buffer (lui/%lo) */

int func_0010E238(void);
int func_0010E338(void);
int func_001293B8(int dst, int src, int len);
int SceSifrpcCall(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);

int func_0010E8A0(int a0) {
    char *p;

    if (func_0010E238() < 0)
        return 0xFFFF0000;
    if (func_0010E338() != 0)
        return 0xFFFEFFFC;
    func_001293B8((int)D_00147388, a0, 0xFC);
    p = (char *)D_00147388 - 8;
    p[0x103] = 0;
    if (SceSifrpcCall((int)D_00147580, 9, 0, (int)p, 0x200, (int)p, 4, 0, 0) < 0)
        return 0xFFFEFFFF;
    return *(int *)((char *)D_00147388 - 8);
}
