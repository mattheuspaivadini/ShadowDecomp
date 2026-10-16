/* asm/cod/011600.s -> func_001240A8.
 * 32x32->64 multu pair; wave3d (R1)
 * MATCHED (Session 8). */
unsigned long long __udivdi3(unsigned long long a0, unsigned long long a1);

unsigned long long TimerUSec2BusClock(unsigned int a0, unsigned int a1) {
    unsigned long long p1;
    unsigned long long p2;

    p1 = (unsigned long long)a0 * 147456000;
    p2 = (unsigned long long)a1 * 147456000;
    return p1 + __udivdi3(p2, 1000000);
}
