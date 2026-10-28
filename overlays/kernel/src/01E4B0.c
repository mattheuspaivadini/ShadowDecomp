/* KERNEL.XFF @ 0x01E4B0 (112 B) - sndSepInitTickParam
 * Evidence: n != 32 -> iosJumpRecoverPoint(.rodata+0x2A80 message); then word +0x48 of the 32 0x70-byte SEP slots (.bss+0x7C3D0) = buf + i * size (pointer copy advanced in the for expression). UNCONFIRMED: names.
 */
struct SepSlot {
    char pad[0x48];
    char *tick;
    char pad4C[0x70 - 0x4C];
};
extern struct SepSlot D_kernel_bss_7C3D0[32];
extern char D_kernel_rodata_2A80[];
void iosJumpRecoverPoint(const char *msg);
void sndSepInitTickParam(char *buf, int n, int size) {
 char *p;
 int i;
 if (n != 32) iosJumpRecoverPoint(D_kernel_rodata_2A80);
 p = buf;
 for (i = 0; i < 32; i++, p += size) D_kernel_bss_7C3D0[i].tick = p;
}
