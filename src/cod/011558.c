/* asm/cod/011558.s -> func_001240A8.
 * unsigned int q makes the remainder multiply multu (was mult, 1 word off)
 * MATCHED (Session 8). */
unsigned long long __udivdi3(unsigned long long a0, unsigned long long a1);

void TimerBusClock2USec(unsigned long long a0, int *a1, int *a2) {
    unsigned int q;
    unsigned long long r;

    q = __udivdi3(a0, 147456000);
    if (a1 != 0)
        *a1 = q;
    if (a2 == 0)
        return;
    r = a0 - (unsigned long long)q * 147456000;
    *a2 = __udivdi3(r * 1000000, 147456000);
}
