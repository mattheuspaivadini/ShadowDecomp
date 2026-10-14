/* probe 2: more shapes for the dsll32/dsra32 pair. */
int gi(int a0, int a1, int a2);
unsigned int gu(int a0, int a1, int a2);

long long g1(int a0) { int r = gi(a0, 0, 10); return ((long long)r << 32) >> 32; }
long long g2(int a0) { return ((long long)gi(a0, 0, 10) << 32) >> 32; }
long long g3(int a0) { return (long long)(unsigned int)gi(a0, 0, 10); }
long long g4(int a0) { unsigned int r = gi(a0, 0, 10); return (long long)(int)r; }
long long g5(int a0) { return (long long)(gi(a0, 0, 10)); }
long long g6(int a0) { long long q = gi(a0, 0, 10) + 0; return q; }
long long g7(int a0) { int r = gu(a0, 0, 10); return ((long long)r << 32) >> 32; }
