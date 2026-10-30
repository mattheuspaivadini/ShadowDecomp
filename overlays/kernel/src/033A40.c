/* KERNEL.XFF @ 0x033A40 (380 B) - sceGsExecLoadImage
 * Evidence: SCE libgraph copy (cc=29). Polls GIF CHCR (0x1000A000) bit 8 with a
 * 0x100-pass timeout that prints "sceGsExecLoadImage: DMA Ch.2 does not
 * terminate" (.rodata+0x36A0) and returns -1; then sends the 6-qword tag packet
 * (QWC=6, MADR=Image, with the scratchpad alias 0x80000000 when the address is
 * in 0x70000000), starts CHCR=0x101, waits again (same timeout counter, not
 * reset), then sends the image itself (QWC = Image->[0x50] & 0x7FFF,
 * MADR=pMem under the same scratchpad rule, CHCR=0x101) and returns 0.
 * UNCONFIRMED: argument names, struct field names.
 * Build: --flags='-G0 -fno-strict-aliasing' --cc=29 (also -G0 and -g0).
 */
#define GIFCHCR (*(volatile unsigned int *)0x1000A000)
#define GIFMADR (*(volatile unsigned int *)0x1000A010)
#define GIFQWC (*(volatile unsigned int *)0x1000A020)

struct LoadImage {
    unsigned long tag0;
    unsigned long regs;
    unsigned long bb;
    unsigned long r0;
    unsigned long tp;
    unsigned long r1;
    unsigned long tr;
    unsigned long r2;
    unsigned long td;
    unsigned long r3;
    unsigned long tag5;
};

int scePrintf(const char *fmt, ...);
extern char D_kernel_rodata_36A0[];

int sceGsExecLoadImage(struct LoadImage *Image, unsigned int pMem) {
    unsigned int loop = 0;

    while (GIFCHCR & 0x100) {
        if (loop++ > 0x1000000) {
            scePrintf(D_kernel_rodata_36A0);
            return -1;
        }
    }
    GIFQWC = 6;
    if (((unsigned int)Image & 0x70000000) == 0x70000000) {
        GIFMADR = ((unsigned int)Image & 0xFFFFFFF) | 0x80000000;
    } else {
        GIFMADR = (unsigned int)Image & 0xFFFFFFF;
    }
    GIFCHCR = 0x101;
    while (GIFCHCR & 0x100) {
        if (loop++ > 0x1000000) {
            scePrintf(D_kernel_rodata_36A0);
            return -1;
        }
    }
    GIFQWC = Image->tag5 & 0x7FFF;
    if ((pMem & 0x70000000) == 0x70000000) {
        GIFMADR = (pMem & 0xFFFFFFF) | 0x80000000;
    } else {
        GIFMADR = pMem & 0xFFFFFFF;
    }
    GIFCHCR = 0x101;
    return 0;
}
