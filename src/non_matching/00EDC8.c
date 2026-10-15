/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 20 [cc=29].
 * R2 w45a_2: block-layout/constants (switch + shared return block)
 * The original .s stays in the build (asm/cod/00EDC8.s); this C
 * draft (Session 8) is kept for the record. */
extern unsigned char D_00147380[];
extern int D_00147580[];

int func_0010E238(void);
int func_00109980(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);

int func_0010EDC8(int a0, unsigned char *a1, unsigned int a2) {
    int r;

    if (func_0010E238() < 0)
        return 0xFFFF0000;
    if (a2 >= 3)
        return 0xFFFEFFFE;
    *(int *)D_00147380 = a0;
    *(int *)(D_00147380 + 4) = (int)a2;
    r = func_00109980((int)D_00147580, 3, 0, (int)D_00147380, 0x20,
                      (int)D_00147380, 0x20, 0, 0);
    if (r < 0)
        return 0xFFFEFFFF;
    switch (a2) {
    case 0:
        *a1 = D_00147380[0];
        break;
    case 1:
        *(unsigned short *)a1 = *(unsigned short *)D_00147380;
        break;
    case 2:
        *(int *)a1 = *(int *)D_00147380;
        break;
    default:
        return 0xFFFEFFFE;
    }
    return 0;
}
