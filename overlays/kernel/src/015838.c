/* KERNEL.XFF @ 0x015838 (52 B) - getTextureAreaAddressFBP
 * Evidence: (w*h >> 11) + 2 * (w2*h2 >> 11): frame-buffer geometry at .bss+0x1F010, four ints (+0,+4,+8,+0xC); the
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

int getTextureAreaAddressFBP(void) {
    return (fb.fbw * fb.fbh >> 11) + (fb.zbw * fb.zbh >> 11) + (fb.zbw * fb.zbh >> 11);
}
