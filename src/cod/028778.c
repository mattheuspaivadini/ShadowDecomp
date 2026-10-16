/* asm/cod/028778.s -> func_00128688.
 * Session 10b: commutative addu operand order fixed by writing index*4 + base
 * MATCHED (Session 8). */
int  _init_signal_r(int a0);
int  _getpid_r(int a0);
int  _kill_r(int a0, int a1, int a2);

int _raise_r(int *ctx, int index) {
    int *e;
    int h;
    int r;

    if ((unsigned int)index >= 0x20) {
        ctx[0] = 0x16;
        return -1;
    }
    if (ctx[0x75] == 0) {
        if (_init_signal_r((int)ctx) != 0)
            return -1;
    }
    e = (int *)(index * 4 + ctx[0x75]);
    h = *e;
    if (h == 0) {
        r = _getpid_r((int)ctx);
        return _kill_r((int)ctx, r, index);
    }
    if (h == 1)
        return 0;
    if (h == -1) {
        ctx[0] = 0x16;
        return 1;
    }
    *e = 0;
    ((void (*)(int))h)(index);
    return 0;
}

