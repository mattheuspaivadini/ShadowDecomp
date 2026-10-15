/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 25 [cc=29].
 * R4 w25a_2: dsll/dsll32 hoisting across the branch
 * The original .s stays in the build (asm/cod/014080.s); this C
 * draft (Session 8) is kept for the record. */
void func_00114080(int a0, int a1, int a2, int a3) {
    unsigned long long v;
    long long w;
    long long h;
    int sx;
    int sy;
    long long x;
    long long y;
    long long hi;

    v = *(unsigned long long *)(a0 + 0x30);
    w = (long long)(int)((v >> 16) & 0x7FF);
    h = (long long)(int)((v >> 48) & 0x7FF);
    sy = (short)a2;
    sx = (short)a1;
    y = (long long)sy - (long long)(((unsigned long long)h + 1) >> 1);
    x = (long long)sx - (long long)(((unsigned long long)w + 1) >> 1);
    if ((short)a3 != 0)
        hi = ((y << 4) + 8) << 32;
    else
        hi = (y << 4) << 32;
    *(long long *)(a0 + 0x20) = (x << 4) | hi;
}
