/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 5 [cc=29].
 * R4 w25a_0: conditional count++ must if-convert to movn
 * The original .s stays in the build (asm/cod/00A120.s); this C
 * draft (Session 8) is kept for the record. */
extern int  D_00132320 __attribute__((section(".data")));
extern char D_00146EC0[];   /* .bss 0x200 bytes = 32 x 0x10 records */

void func_0010A0B0(void);
void func_00107020(int a0);
void func_00107000(int a0);

int func_0010A120(void) {
    int  count = 0;
    int *p;
    int *end;

    func_0010A0B0();
    func_00107020(D_00132320);
    p = (int *)D_00146EC0;
    end = p + 0x80;
    for (; p < end; p += 4) {
        if (p[1] != 0)
            count++;
    }
    func_00107000(D_00132320);
    return count;
}
