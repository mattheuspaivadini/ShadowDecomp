/* asm/cod/010588.s -> EndTimer.
 * timer EndTimer; volatile counter-in-use word, handler removal guards the T2 reset (Session 19)
 * MATCHED. */
struct S10588 {
    long long base;   /* 0x00 */
    int       f08;    /* 0x08 */
    int       f0C;    /* 0x0C */
    volatile int f10; /* 0x10 */
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

    if (D_00133918.f08 < 0)
        return 0x80008001;
    if (D_00133918.f10 != 0)
        return 0x80000010;
    guard = DIntr();
    if (RemoveIntcHandler(0xB, D_00133918.f08) == 0) {
        DisableIntc(0xB);
        SetT2_MODE(0xC00);
        SetT2_COUNT(0);
    }
    D_00133918.base = 0;
    D_00133918.f08 = -1;
    if (guard != 0)
        EIntr();
    return 0;
}
