/* asm/cod/0114D8.s -> func_0010FB20.
 * R4 w25a_1 (4-arg guard wrapper, a1 = long long)
 * MATCHED (Session 8). */
int DIntr(void);
int EIntr(void);
int iSetTimerHandler(int a0, long long a1, int a2, int a3);

int SetTimerHandler(int a0, long long a1, int a2, int a3) {
    int g;
    int b;

    g = DIntr();
    b = iSetTimerHandler(a0, a1, a2, a3);
    if (g != 0)
        EIntr();
    return b;
}
