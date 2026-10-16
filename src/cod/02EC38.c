/* asm/cod/02EC38.s -> _i2b.
 * _i2b: exact newlib mprec.c BigInt
 * MATCHED (Session 12). */
struct _Bigint {
    struct _Bigint *_next;
    int _k;
    int _maxwds;
    int _sign;
    int _wds;
    int _x[1];
};

struct _Bigint *_Balloc(void *ptr, int k);

struct _Bigint *_i2b(void *ptr, int i) {
    struct _Bigint *b;

    b = _Balloc(ptr, 1);
    b->_x[0] = i;
    b->_wds = 1;
    return b;
}
