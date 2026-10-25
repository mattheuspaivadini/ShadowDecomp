/* KERNEL.XFF @ 0x01B498 (100 B) - addVIntrTime
 * Evidence: t->frac = f - elapsed, with d = (float)(vsync counter (volatile .data+0x7D4) - t->count); q = (float)(int)(d / 59.94) (as d * 0.01668335f); the elapsed time is q + (d - q * 59.94) / 59.94; the constants are the decimal literals 0.01668335 and 59.94 (images 0x3C88AB85/0x426FC28F).
 */
struct VIntrTime {
    int count;
    float frac;
};
extern volatile int D_kernel_data_07D4;

void addVIntrTime(struct VIntrTime *t, float f) {
    float d = (float)(D_kernel_data_07D4 - t->count);
    float q = (float)(int)(d * 0.01668335f);

    t->frac = f - (q + (d - q * 59.94f) * 0.01668335f);
}
