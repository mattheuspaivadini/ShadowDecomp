/* MANAGER.XFF @ 0x009008 (20 B) - GAMEUTIL_forward_timer_still_one_ratio_time_interp_ratio_cntrl
 * Evidence:
 *   lwc1 f0,0x14(a0) / lwc1 f1,0x18(a0) / add.s f0,f0,f1 / jr / swc1 f0,0xc(a0)
 * i.e. field(+0xC) = field(+0x14) + field(+0x18), all 32-bit floats. The store
 * sits in the `jr` delay slot (reorg).
 * UNCONFIRMED: field names; the offsets and the 32-bit width are the evidence.
 */
void GAMEUTIL_forward_timer_still_one_ratio_time_interp_ratio_cntrl(unsigned char *p) {
    *(float *)(p + 0xC) = *(float *)(p + 0x14) + *(float *)(p + 0x18);
}
