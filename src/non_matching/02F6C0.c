/* STATUS (10, 2026-10-16): NON_MATCHING. best score 44 [cc=29].
 * 
 * The original .s stays in the build (asm/cod/02F6C0.s); this C
 * draft (10) is kept for the record. */
struct _Bigint {
    struct _Bigint *_next;
    int _k;
    int _maxwds;
    int _sign;
    int _wds;
    int _x[1];
};

extern double _b2d(struct _Bigint *a, int *e);

#define word0(x) ((unsigned int *)&x)[1]
#define Exp_msk1 0x100000

double _ratio(struct _Bigint *a, struct _Bigint *b) {
    double da, db;
    int k, ka, kb;

    da = _b2d(a, &ka);
    db = _b2d(b, &kb);
    k = ka - kb + 32 * (a->_wds - b->_wds);
    if (k > 0)
        word0(da) += k * Exp_msk1;
    else {
        k = -k;
        word0(db) += k * Exp_msk1;
    }
    return da / db;
}
