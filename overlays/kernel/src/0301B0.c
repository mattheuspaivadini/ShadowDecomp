typedef struct {
    char pad0[0x1C];
    float x2;      /* 0x1C */
    float x1;      /* 0x20 */
    float y2;      /* 0x24 */
    float y1;      /* 0x28 */
    char pad1[0x08];
    float b0;      /* 0x34 */
    float b1;      /* 0x38 */
    float b2;      /* 0x3C */
    float a1;      /* 0x40 */
    float a2;      /* 0x44 */
} TIIR;

void IirFilter(TIIR *st, int n, float *buf) {
    float b0 = st->b0;
    float b1 = st->b1;
    float b2 = st->b2;
    float a1 = st->a1;
    float a2 = st->a2;
    float x[3];
    int i;

    x[0] = buf[0];
    x[1] = buf[1];
    x[2] = buf[2];
    buf[0] = b0 * x[0] + b1 * st->x1 + b2 * st->x2 - a1 * st->y1 - a2 * st->y2;
    buf[1] = b0 * x[1] + b1 * x[0] + b2 * st->x1 - a1 * buf[0] - a2 * st->y1;
    for (i = 2; i < n; i++) {
        buf[i] = b0 * x[2] + b1 * x[1] + b2 * x[0]
               - a1 * buf[i - 1] - a2 * buf[i - 2];
        x[0] = x[1];
        x[1] = x[2];
        x[2] = buf[i + 1];
    }
    st->x2 = x[0];
    st->x1 = x[1];
    st->y2 = buf[n - 2];
    st->y1 = buf[n - 1];
}
