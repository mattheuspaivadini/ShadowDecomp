/* probe: which source shape emits dsll32/dsra32 (sign-extend int -> long long)? */
int gi(int a0, int a1, int a2);
unsigned int gu(int a0, int a1, int a2);

long long f1(int a0) { return (long long)gi(a0, 0, 10); }
long long f2(int a0) { int r = gi(a0, 0, 10); return (long long)r; }
long long f3(int a0) { return gi(a0, 0, 10) << 32 >> 32; }
long long f4(int a0) { return (long long)(int)gu(a0, 0, 10); }
long long f5(int a0) { long long r = gi(a0, 0, 10); return r; }
long long f6(int a0) { int r = gi(a0, 0, 10); long long q = r; return q; }
