/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 21 [cc=29].
 * R2 w45a_2: reg-alloc (reply load vs byte-store base)
 * The original .s stays in the build (asm/cod/00EC78.s); this C
 * draft (Session 8) is kept for the record. */
extern unsigned char D_00147388[];
extern int D_00147580[];

int func_0010E238(void);
int func_0010E338(void);
void func_001293B8(char *dst, char *src, int n);
int func_00109980(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);

int func_0010EC78(char *a0, char *a1, int *a2, int a3) {
    char *p;
    int r;
    int v;

    if (func_0010E238() < 0)
        return 0xFFFF0000;
    if (func_0010E338() != 0)
        return 0xFFFEFFFC;
    p = (char *)(D_00147388 - 8);
    func_001293B8((char *)D_00147388, a0, 0xFC);
    p[0x103] = 0;
    func_001293B8((char *)D_00147388 + 0xFC, a1, 0xFC);
    p[0x1FF] = 0;
    r = func_00109980((int)D_00147580, a3, 0, (int)p, 0x200, (int)p, 0x10,
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
