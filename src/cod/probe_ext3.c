/* probe 3: signed 32->64 extension with a long long-typed callee. */
long long gk(int a0, int a1, int a2);

long long g8(int a0) { return (int)gk(a0, 0, 10); }
long long g9(int a0) { return gk(a0, 0, 10) << 32 >> 32; }
long long g10(int a0) { return (long long)(int)gk(a0, 0, 10); }
int g11(int a0) { return gk(a0, 0, 10); }
