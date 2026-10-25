/* KERNEL.XFF @ 0x0161B8 (68 B) - InitGp
 * Evidence: sceGsResetPath(); sceGsSyncPath(0, 0); iosInitDC(); then words +0xA0 = 1 and +0xA4 = 0 of the frame-buffer block at .bss+0x1F010 (two fields through one base). UNCONFIRMED: field names.
 */
struct FrameBuf {
    int fbw;
    int fbh;
    int zbw;
    int zbh;
    char pad[0x90];
    int unkA0;
    int unkA4;
};
extern struct FrameBuf D_kernel_bss_1F010;
void sceGsResetPath(void);
void sceGsSyncPath(int mode, unsigned short timeout);
void iosInitDC(void);

void InitGp(void) {
    sceGsResetPath();
    sceGsSyncPath(0, 0);
    iosInitDC();
    D_kernel_bss_1F010.unkA0 = 1;
    D_kernel_bss_1F010.unkA4 = 0;
}
