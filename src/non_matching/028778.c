/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 1 [cc=296].
 * session9 R2 waveA; residual class not auto-classified
 * The original .s stays in the build (asm/cod/028778.s); this C
 * draft (Session 9) is kept for the record. */
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
    e = (int *)(ctx[0x75] + index * 4);
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
