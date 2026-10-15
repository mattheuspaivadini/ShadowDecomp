/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 15 [cc=29].
 * R1 wave4c: GS_CSR bit 13 vs long long callee
 * The original .s stays in the build (asm/cod/013B60.s); this C
 * draft (Session 8) is kept for the record. */
struct S13B60 {
    short f00;          /* 0x00 */
    char  pad02[6];
    int   f08;          /* 0x08 */
};

extern struct S13B60 D_00133970[];
int func_00113520(void);
int func_00111D60(void);
long long func_00111DF0(void);

int func_00113B60(void) {
    struct S13B60 *p = (struct S13B60 *)func_00113520();

    if (p->f08 == 0) {
        func_00111D60();
        if (p->f00 != 1)
            return 1;
        return (int)((*(volatile unsigned long long *)0x12001000U >> 13) & 1);
    } else {
        long long r = func_00111DF0();

        if (p->f00 != 1)
            return 1;
        return (int)((r >> 13) & 1);
    }
}
