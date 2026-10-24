/* MANAGER.XFF @ 0x009248 (20 B) - set_param_double_spring_interp_common
 * Evidence: four `swc1` stores of the four float arguments:
 *   $f12 -> +0x0, $f13 -> +0x4, $f14 -> +0x8, $f15 -> +0xC,
 * emitted as +0xC, +0x0, +0x4, +0x8 (`jr` before the last store): sched2 rotates
 * the four independent stores right by one, so the source keeps the natural
 * ascending order. Field names UNCONFIRMED.
 */
void set_param_double_spring_interp_common(unsigned char *p, float a, float b,
                                           float c, float d) {
    *(float *)(p + 0x0) = a;
    *(float *)(p + 0x4) = b;
    *(float *)(p + 0x8) = c;
    *(float *)(p + 0xC) = d;
}
