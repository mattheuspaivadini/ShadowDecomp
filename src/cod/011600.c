/* asm/cod/011600.s -> func_001240A8.
 * 32x32->64 multu pair; wave3d (R1)
 * MATCHED (Session 8). */
unsigned long long func_001240A8(unsigned long long a0, unsigned long long a1);

unsigned long long func_00111600(unsigned int a0, unsigned int a1) {
    unsigned long long p1;
    unsigned long long p2;

    p1 = (unsigned long long)a0 * 147456000;
    p2 = (unsigned long long)a1 * 147456000;
    return p1 + func_001240A8(p2, 1000000);
}
