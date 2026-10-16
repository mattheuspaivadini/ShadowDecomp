/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 15 [cc=29].
 * R2 w45a_3: state validation + two-arm install
 * The original .s stays in the build (asm/cod/010588.s); this C
 * draft (Session 8) is kept for the record. */
struct S10588 {
    long long base;   /* 0x00 */
    int       f08;    /* 0x08 */
    int       f0C;    /* 0x0C */
    int       f10;    /* 0x10 */
};

extern struct S10588 D_00133918;
int DIntr(void);
int RemoveIntcHandler(int a0, int a1);
int DisableIntc(int a0);
int SetT2_MODE(int a0);
int SetT2_COUNT(int a0);
int EIntr(void);

int EndTimer(void) {
    int guard;
    int r;

    if (D_00133918.f08 < 0)
        return 0x80008001;
    if (D_00133918.f10 != 0)
        return 0x80000010;
    guard = DIntr();
    if (RemoveIntcHandler(0xB, D_00133918.f08) != 0) {
        r = -1;
    } else {
        DisableIntc(0xB);
        SetT2_MODE(0xC00);
        SetT2_COUNT(0);
        r = -1;
    }
    D_00133918.base = 0;
    D_00133918.f08 = r;
    if (guard != 0)
        EIntr();
    return 0;
}
