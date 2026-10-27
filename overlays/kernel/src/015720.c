/* KERNEL.XFF @ 0x015720 (48 B) - getFrameBufferSizeTBP
 * Evidence: (w*h + w2*h2*2) >> 6: frame-buffer geometry at .bss+0x1F010, four ints (+0,+4,+8,+0xC); the
 * 16-bit pixel area is w*h + w2*h2*2 bytes, and >>6 / >>11 convert to TBP
 * (64-word) / FBP (2048-word) units. mult/mult1 are the R5900 three-operand
 * multiplies. UNCONFIRMED: field names.
 */
struct FrameBuf {
    int fbw;
    int fbh;
    int zbw;
    int zbh;
};
extern struct FrameBuf D_kernel_bss_1F010;
#define fb D_kernel_bss_1F010

int getFrameBufferSizeTBP(void) {
    return (fb.fbw * fb.fbh + fb.zbw * fb.zbh * 2) >> 6;
}
