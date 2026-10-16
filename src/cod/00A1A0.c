/* asm/cod/00A1A0.s -> func_0010A0B0.
 * empty-asm register pin on dummy return of func_00107020
 * MATCHED (Session 8). */
extern int  D_00132320 __attribute__((section(".data")));
extern char D_00146EC0[];

void func_0010A0B0(void);
int func_00107020(int a0);
void func_00107000(int a0);

int *func_0010A1A0(void) {
    int *p;
    int *end;
    int dummy;

    func_0010A0B0();
    dummy = func_00107020(D_00132320);
    asm volatile ("" : "+r" (dummy));
    p = (int *)D_00146EC0;
    end = p + 0x80;
    for (; p < end; p += 4) {
        if (p[1] != 0)
            continue;
        p[1] = 0x10000000;
        func_00107000(D_00132320);
        return p;
    }
    func_00107000(D_00132320);
    return 0;
}