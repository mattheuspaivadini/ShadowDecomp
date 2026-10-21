/* asm/cod/007E20.s -> func_00107E20.
 * %e formatter; -G0 TU: the 0.1/0.1/1e6 literals are GAS li.d pool entries (adopted .rodata at 0x137CF8) (Session 44)
 * MATCHED. */
extern char D_00137CE0[];   /* "0.%d" */
extern char D_00137CE8[];   /* "e+%d" */
extern char D_00137CF0[];   /* "e%d" */
int func_00107D90(unsigned long m);
int func_00108DB8(int (*cb)(), int a1, int *a2, char *fmt, ...);

int func_00107E20(int (*cb)(), int arg, int *left, double d)
{
    int n = 0;
    int e = 0;
    int m;

    if (*left == 0)
        return 0;
    if (d < 0.0) {
        d = 0.0 - d;
        n = 1;
        cb(arg, left, '-');
        (*left)--;
    }
    if (d < 0.1) {
        while (d < 0.1) {
            e--;
            d = d * 10.0;
        }
    } else if (d >= 1.0) {
        while (d >= 1.0) {
            e++;
            d = d / 10.0;
        }
    }
    m = func_00107D90((unsigned long)(d * 1000000.0));
    n += func_00108DB8(cb, arg, left, D_00137CE0, m);
    if (e >= 0)
        n += func_00108DB8(cb, arg, left, D_00137CE8, e);
    else
        n += func_00108DB8(cb, arg, left, D_00137CF0, e);
    return n;
}
