/* KERNEL.XFF @ 0x01B430 (100 B) - getVIntrDiffTime
 * Evidence: returns the elapsed seconds plus t->frac: d = (float)(vsync counter (volatile .data+0x7D4) - t->count); q = (float)(int)(d / 59.94) (as d * 0.01668335f); the elapsed time is q + (d - q * 59.94) / 59.94; the constants are the decimal literals 0.01668335 and 59.94 (images 0x3C88AB85/0x426FC28F). UNCONFIRMED: field names.
 */
struct VIntrTime {
    int count;
    float frac;
};
extern volatile int D_kernel_data_07D4;

float getVIntrDiffTime(struct VIntrTime *t) {
    float d = (float)(D_kernel_data_07D4 - t->count);
    float q = (float)(int)(d * 0.01668335f);

    return q + (d - q * 59.94f) * 0.01668335f + t->frac;
}
