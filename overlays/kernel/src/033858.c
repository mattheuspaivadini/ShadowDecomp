/* KERNEL.XFF @ 0x033858 (484 B) - sceGsSetDefLoadImage
 * Evidence: SCE libgraph copy (cc=29 frame). The 4th argument selects a 59-entry
 * jump table at .rodata+0x35B0 (.text+0x338C4/338D0/338E4/338F0/338FC for
 * PSM 0/48, 1/49, 2/10/50/58, 19/27, 20/36/44), i.e. bytes/pixel 4, 3, 2, 1,
 * 0.5 -> qwc = width*height {>>2, *3>>4, >>3, >>4, >>5} on the 7th/8th short
 * arguments. qwc > 0x7FFF prints "sceGsSetDefLoadImage: too big size" (.rodata
 * +0x3580) and returns NULL. Otherwise two 128-bit tag qwords (0x00, 0x50) are
 * cleared and re-filled as GIF tags: NLOOP=4/NREG=1 at 0x00, REGS low nibble
 * 0xE at 0x08, NLOOP=qwc/EOP at 0x50 with FLG=2 (image mode); the register list
 * 0x50..0x53 (BITBLTBUF/TRXPOS/TRXREG/TRXDIR) is built from the remaining
 * shorts, then `sync` and return 6 (the packet is 6 qwords).
 * UNCONFIRMED: the argument names (only their bit positions are proved).
 * Build: --flags='-G0 -fno-strict-aliasing' --cc=29 (also matches with -G0
 * alone and with -g0; the default 2.96 compiler does not).
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));

typedef struct {
    unsigned long nloop : 15;
    unsigned long eop : 1;
    unsigned long pad0 : 30;
    unsigned long pre : 1;
    unsigned long prim : 11;
    unsigned long flg : 2;
    unsigned long nreg : 4;
} GifTag;

typedef struct {
    unsigned long r0 : 4;
    unsigned long rest : 60;
} GifRegs;

struct LoadImage {
    GifTag tag;
    GifRegs regs;
    unsigned long bb;
    unsigned long r0;
    unsigned long tp;
    unsigned long r1;
    unsigned long tr;
    unsigned long r2;
    unsigned long td;
    unsigned long r3;
    GifTag qwc_tag;
    unsigned long pad5;
};

int scePrintf(const char *fmt, ...);
extern char D_kernel_rodata_3580[];

int sceGsSetDefLoadImage(struct LoadImage *Image, short arg2, short arg3, short arg4,
                         short arg5, short arg6, short arg7, short arg8) {
    int qwc = 0;

    switch (arg4) {
    case 0:
    case 0x30:
        qwc = arg7 * arg8 >> 2;
        break;
    case 1:
    case 0x31:
        qwc = arg7 * arg8 * 3 >> 4;
        break;
    case 2:
    case 10:
    case 0x32:
    case 0x3A:
        qwc = arg7 * arg8 >> 3;
        break;
    case 0x13:
    case 0x1B:
        qwc = arg7 * arg8 >> 4;
        break;
    case 0x14:
    case 0x24:
    case 0x2C:
        qwc = arg7 * arg8 >> 5;
        break;
    }
    if (qwc > 0x7FFF) {
        scePrintf(D_kernel_rodata_3580);
        return 0;
    }
    *(u_long128 *)&Image->qwc_tag = 0;
    *(u_long128 *)&Image->tag = 0;
    Image->tag.nloop = 4;
    Image->tag.nreg = 1;
    Image->regs.r0 = 0xE;
    Image->bb = ((unsigned long)arg2 << 32) | ((unsigned long)arg3 << 48) |
               ((unsigned long)arg4 << 56);
    Image->r0 = 0x50;
    Image->tp = ((unsigned long)arg5 << 32) | ((unsigned long)arg6 << 48);
    Image->r1 = 0x51;
    Image->tr = (unsigned long)arg7 | ((unsigned long)arg8 << 32);
    Image->r2 = 0x52;
    Image->r3 = 0x53;
    Image->td = 0;
    Image->qwc_tag.nloop = qwc;
    Image->qwc_tag.eop = 1;
    Image->qwc_tag.flg = 2;
    __asm__ volatile("sync");
    return 6;
}
