/* STATUS (Session 35, 2026-10-19): NON_MATCHING. best score 106 [cc=29].
 * %e formatter: sign, decimal exponent by x10 / /10 loops, mantissa via (unsigned long)(d * 1e6).
 * The original uses literal doubles (constant-pool loads lui at + ld at the image labels
 * D_00137CF8/D_00137D00/D_00137D08). With literals the draft reaches 15 but a C object cannot add
 * .rodata; with the image labels as externs the 1.0/10.0 constants get hoisted (106). Tried:
 * const/array externs, -G0.
 * The original .s stays in the build (asm/cod/007E20.s); this C
 * draft (Session 35) is kept for the record. */
extern double D_00137CF8[];   /* 0.1 */
extern double D_00137D00[];   /* 0.1 */
extern double D_00137D08[];   /* 1000000.0 */
extern char D_00137CE0[];   /* "0.%d" */
extern char D_00137CE8[];   /* "e+%d" */
extern char D_00137CF0[];   /* "e%d" */
int func_00107D90(unsigned long m);
int func_00108DB8(int (*cb)(), int a1, int *a2, char *fmt, ...);

int func_00107E20(int (*cb)(), int arg, int *left, double d)
{
    int n = 0;
    int e = 0;

    if (*left == 0)
        return 0;
    if (d < 0.0) {
        d = 0.0 - d;
        n = 1;
        cb(arg, left, '-');
        (*left)--;
    }
    if (d < D_00137CF8[0]) {
        while (d < D_00137D00[0]) {
            e--;
            d = d * 10.0;
        }
    } else if (d >= 1.0) {
        while (d >= 1.0) {
            e++;
            d = d / 10.0;
        }
    }
    n += func_00108DB8(cb, arg, left, D_00137CE0, func_00107D90((unsigned long)(d * D_00137D08[0])));
    if (e < 0)
        n += func_00108DB8(cb, arg, left, D_00137CF0, e);
    else
        n += func_00108DB8(cb, arg, left, D_00137CE8, e);
    return n;
}
