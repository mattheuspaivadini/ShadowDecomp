/* KERNEL.XFF @ 0x009338 (340 B) - isysGetXffEntryPointPreRelocation
 * Evidence: sets the section table pointer (+0x30 = header + offset at +0x5C), then for sections 1..n-1 (0x20 bytes) sets addr = header + file offset; non-empty PROGBITS (1) or type 0x7FFFF420 sections must have no flags (.rodata+0xA60) and an aligned address (.rodata+0xAC0) and give the entry point addr + header entry (+0x4C); a non-empty NOBITS (8) is reported (.rodata+0xB28). Returns 0 when nothing qualifies. Section type unsigned (sltiu). UNCONFIRMED: names.
 */
struct XffSect {
    int unk0;
    unsigned int addr;
    int size;
    int align;
    unsigned int type;
    int flags;
    int unk18;
    int offset;
};
struct XffHdr {
    char pad0[0x30];
    struct XffSect *sects;
    char pad34[0xC];
    int nsect;
    char pad44[8];
    int entry;
    char pad50[0xC];
    int sectoff;
};
extern char D_kernel_rodata_0A60[];
extern char D_kernel_rodata_0AC0[];
extern char D_kernel_rodata_0B28[];
void iosJumpRecoverPoint(const char *fmt, ...);

int isysGetXffEntryPointPreRelocation(struct XffHdr *h) {
    struct XffSect *s;
    int i;

    h->sects = (struct XffSect *)((char *)h + h->sectoff);
    s = &h->sects[1];
    for (i = 1; i < h->nsect; i++, s++) {
        s->addr = (unsigned int)h + s->offset;
        if (s->size == 0) {
            continue;
        }
        switch (s->type) {
        case 1:
        case 0x7FFFF420:
            if (s->flags != 0) {
                iosJumpRecoverPoint(D_kernel_rodata_0A60);
                break;
            }
            if (s->addr & (s->align - 1)) {
                iosJumpRecoverPoint(D_kernel_rodata_0AC0, s->align);
                break;
            }
            return s->addr + h->entry;
        case 8:
            iosJumpRecoverPoint(D_kernel_rodata_0B28, s->align);
            break;
        }
    }
    return 0;
}
