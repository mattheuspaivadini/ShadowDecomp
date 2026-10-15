/* asm/cod/028778.s -> func_00128688.
 * Session 10b: commutative addu operand order fixed by writing index*4 + base
 * MATCHED (Session 8). */
int  func_00128688(int a0);
int  func_001289D0(int a0);
int  func_00128970(int a0, int a1, int a2);

int func_00128778(int *ctx, int index) {
    int *e;
    int h;
    int r;

    if ((unsigned int)index >= 0x20) {
        ctx[0] = 0x16;
        return -1;
    }
    if (ctx[0x75] == 0) {
        if (func_00128688((int)ctx) != 0)
            return -1;
    }
    e = (int *)(index * 4 + ctx[0x75]);
    h = *e;
    if (h == 0) {
        r = func_001289D0((int)ctx);
        return func_00128970((int)ctx, r, index);
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

