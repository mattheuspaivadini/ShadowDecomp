/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 46 [cc=296].
 * session9 R2 waveA; residual class not auto-classified
 * The original .s stays in the build (asm/cod/02EE80.s); this C
 * draft (Session 9) is kept for the record. */
struct N02EE80 {
    struct N02EE80 *f00;     /* 0x00 child link */
};

struct P02EE80 {             /* a0 */
    char pad00[0x48];
    struct N02EE80 *f48;     /* 0x48 */
};

extern int D_00139B4C[];     /* absolute-addressed coefficient table */

void *_multadd(struct P02EE80 *a0, void *a1, int coeff, int a3);
void *_i2b(struct P02EE80 *a0, int size);
void *_multiply(struct P02EE80 *a0, void *a1, void *a2);
void _Bfree(struct P02EE80 *a0, void *node);

void *_pow5mult(struct P02EE80 *a0, void *a1, int a2) {
    struct N02EE80 *n;
    struct N02EE80 *v;
    int k;

    if ((a2 & 3) != 0)
        a1 = _multadd(a0, a1, D_00139B4C[a2 & 3], 0);
    k = a2 >> 2;
    if (k == 0)
        return a1;
    n = a0->f48;
    if (n == 0) {
        n = _i2b(a0, 0x271);
        a0->f48 = n;
        n->f00 = 0;
    }
    for (;;) {
        if (k & 1) {
            v = _multiply(a0, a1, n);
            _Bfree(a0, a1);
            a1 = v;
        }
        k >>= 1;
        if (k == 0)
            break;
        if (n->f00 != 0) {
            n = n->f00;
        } else {
            v = _multiply(a0, n, n);
            n->f00 = v;
            v->f00 = 0;
            n = v;
        }
    }
    return a1;
}
