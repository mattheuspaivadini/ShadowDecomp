/* KERNEL.XFF @ 0x013298 (196 B) - iosDlChainHead
 * Evidence: takes a 0x20-byte packet from the work pointer (+0x20, volatile pref 0x40), writes tag (addr << 32 | 0x50000000) and zero words +0x1C/+0x18/+0xC/+0x8 (that source order schedules to the image), a NEXT tag to the record's previous head (+0x20), makes the packet the new head and patches the record tag to id 5 with addr = packet. DL work block at .bss+0x1EAD8 (volatile struct, see iosDlGetLayer); chain records are 0x30 bytes in buf[workBufId] (a 64-bit DMA tag, then the head packet pointer at +0x20). UNCONFIRMED: names, DmaTag bitfield layout (EE DMA tag: qwc:16, id at bit 28, addr:31 at bit 32).
 */
struct DLWork {
    char *base[2];
    char *buf[2];
    char *packet;
    int layerNum;
    int workBufId;
    int layer;
};
extern volatile struct DLWork D_kernel_bss_1EAD8;
typedef struct {
    unsigned long qwc:16;
    unsigned long pad:10;
    unsigned long pce:2;
    unsigned long id:3;
    unsigned long irq:1;
    unsigned long addr:31;
    unsigned long spr:1;
} DmaTag;
struct DLChain {
    DmaTag tag;
    unsigned long pad8;
    unsigned long pad10;
    unsigned long pad18;
    unsigned int head;
    unsigned int tail;
    unsigned long pad28;
};
void iosDlChainHead(int slot, int addr) {
    struct DLChain *c;
    unsigned long *p;

    c = &((struct DLChain *)D_kernel_bss_1EAD8.buf[D_kernel_bss_1EAD8.workBufId])[slot];
    p = (unsigned long *)D_kernel_bss_1EAD8.packet;
    D_kernel_bss_1EAD8.packet += 0x20;
    __asm__ __volatile__("pref 0, 0x40(%0)" : : "r"(p));
    p[0] = ((unsigned long)addr << 32) | 0x50000000;
    ((int *)p)[7] = 0;
    ((int *)p)[6] = 0;
    ((int *)p)[3] = 0;
    ((int *)p)[2] = 0;
    p[2] = ((unsigned long)c->head << 32) | 0x20000000;
    c->head = (unsigned int)p;
    c->tag.addr = (unsigned int)p;
    c->tag.id = 5;
}
