/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 46 [cc=296].
 * R2 w45a_0: block-layout (i==9 continue + cross-jumped calls)
 * The original .s stays in the build (asm/cod/0020C0.s); this C
 * draft (Session 8) is kept for the record. */
extern int  D_00131D00[];
extern int  D_00131D80[];
extern char start[];

void func_0010F2D8(int a0, int a1);
void func_001021E0(int a0, int a1, int a2, int a3, int a4, int a5);
void func_00102360(int a0, int a1, int a2, int a3, int a4, int a5);

void func_001020C0(void) {
    int *q;
    int i;
    int *p;

    q = (int *)D_00131D00;
    for (i = 0; i < 0xE; i++, q++) {
        if (i == 8)
            continue;
        if (i < 9) {
            if (i == 0)
                continue;
            func_0010F2D8(q[0], (int)func_001021E0);
        } else if (i == 9) {
            func_0010F2D8(*(int *)((char *)D_00131D00 + 0x48), (int)func_00102360);
            continue;
        } else {
            func_0010F2D8(q[0], (int)func_001021E0);
        }
    }
    p = (int *)((char *)D_00131D80 + 0x1F8);
    for (i = 0x3F; i >= 0; i--) {
        *p = 0;
        p -= 2;
    }
    *(int *)((char *)D_00131D80 + 0x0E8) = (int)__builtin_frame_address(0);
    *(int *)((char *)D_00131D80 + 0x170) = (int)start;
    *(int *)((char *)D_00131D80 + 0x0F8) = (int)start;
}
