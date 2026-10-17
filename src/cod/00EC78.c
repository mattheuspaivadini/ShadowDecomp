/* asm/cod/00EC78.s -> func_0010EC78.
 * swap_stmt_5: two statements reordered (Session 20, corrected permute_gen)
 * MATCHED. */
extern unsigned char D_00147388[];
extern int D_00147580[];

int func_0010E238(void);
int func_0010E338(void);
void func_001293B8(char *dst, char *src, int n);
int sceSifCallRpc(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);

int func_0010EC78(char *a0, char *a1, int *a2, int a3) {
    char *p;
    int r;
    int v;

    if (func_0010E238() < 0)
        return 0xFFFF0000;
    if (func_0010E338() != 0)
        return 0xFFFEFFFC;
    func_001293B8((char *)D_00147388, a0, 0xFC);
    p = (char *)(D_00147388 - 8);
    p[0x103] = 0;
    func_001293B8((char *)D_00147388 + 0xFC, a1, 0xFC);
    p[0x1FF] = 0;
    r = sceSifCallRpc((int)D_00147580, a3, 0, (int)p, 0x200, (int)p, 0x10,
                      0, 0);
    if (r < 0)
        return 0xFFFEFFFF;
    v = *(int *)(D_00147388 - 8);
    if (v == 0)
        return 0xFFFEFFFD;
    *a2 = v;
    a2[1] = *(int *)(p + 4);
    return 0;
}
