/* asm/cod/027460.s -> func_00127460.
 * atexit (matched after T004 split from 027448)
 * MATCHED (Session 12). */
struct _atexit {
    struct _atexit *_next;
    int _ind;
    void (*_fns[32])(void);
};

struct _reent_atexit {
    char pad[0x148];
    struct _atexit *_atexit;
    struct _atexit _atexit0;
};

extern __attribute__((section(".data"))) struct _reent_atexit *_impure_ptr;
void *malloc(unsigned int size);

int func_00127460(void (*fn)(void)) {
    struct _atexit *p;
    if ((p = _impure_ptr->_atexit) == 0)
        _impure_ptr->_atexit = p = &_impure_ptr->_atexit0;
    if (p->_ind >= 32) {
        if ((p = (struct _atexit *)malloc(sizeof(*p))) == 0)
            return -1;
        p->_ind = 0;
        p->_next = _impure_ptr->_atexit;
        _impure_ptr->_atexit = p;
    }
    p->_fns[p->_ind++] = fn;
    return 0;
}
