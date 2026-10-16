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
int sceGsGetGParam(void);
int VSync(void);
long long VSync2(void);

int sceGsSyncV(void) {
    struct S13B60 *p = (struct S13B60 *)sceGsGetGParam();

    if (p->f08 == 0) {
        VSync();
        if (p->f00 != 1)
            return 1;
        return (int)((*(volatile unsigned long long *)0x12001000U >> 13) & 1);
    } else {
        long long r = VSync2();

        if (p->f00 != 1)
            return 1;
        return (int)((r >> 13) & 1);
    }
}
