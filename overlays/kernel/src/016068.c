/* KERNEL.XFF @ 0x016068 (104 B) - iosGsResetCRTC
 * Evidence: for both 0x38-byte display records at .bss+0x1F020: bit 0 and bit 5 of word +8 = (.bss+0x1F0B0 & 1), the global re-read for each bitfield store; tail call to the static at .text+0x14BA0. UNCONFIRMED: field names.
 */
struct GsDispReg {
    char pad0[8];
    unsigned int en1 : 1;
    unsigned int pad1 : 4;
    unsigned int crtmd : 1;
    unsigned int pad6 : 26;
    char padC[0x38 - 0xC];
};
struct GsCrtc {
    char pad0[0x10];
    struct GsDispReg disp[2];
    char pad80[0xA0 - 0x80];
    int inter;
};
extern struct GsCrtc D_kernel_bss_1F010;
void func_014BA0(void);

void iosGsResetCRTC(void) {
    int i;

    for (i = 0; i < 2; i++) {
        D_kernel_bss_1F010.disp[i].en1 = D_kernel_bss_1F010.inter & 1;
        D_kernel_bss_1F010.disp[i].crtmd = D_kernel_bss_1F010.inter & 1;
    }
    func_014BA0();
}
