/* v03: callee declared as returning a 64-bit type; wrapper returns int.
 * GCC then sign-extends the low 32 bits with dsll32/dsra32 (probe_ext3 g11). */
long long func_00129800(int a0, int a1, int a2);

int func_00127500(int a0) {
    return func_00129800(a0, 0, 10);
}
