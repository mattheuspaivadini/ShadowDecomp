/* KERNEL.XFF @ 0x013360 (196 B) - iosDlChainTail
 * Evidence: sibling of iosDlChainHead (013428): same DL work block at .bss+0x1EAD8 and 0x30-byte chain records; allocates a 0x20-byte packet (pref 0x40), writes the 64-bit tag (addr << 32 | 0x50000000) and zeroes words 2/3/6/7, then links it after the chain tail (+0x24): p->next (+0x10 tag) takes the old tail's next address, tail->next = p, chain->tail = p. UNCONFIRMED: names, DmaTag layout.
 * Levers: lwu + and + dsll32/dsra32/dsll32 needs the next address read as a bitfield (DmaTag.addr) widened to unsigned long x with an empty asm "+r"(x) before (int)x << 32 (otherwise gcc drops the sign extension); no t temp for the second access, c->tail re-read in the expression.
 * c_sources: 013360 = src/013360.c -G0 -fno-strict-aliasing
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
struct DLPkt {
    unsigned long t0;
    unsigned long t1;
    DmaTag tag;
};

void iosDlChainTail(int slot, int addr) {
    struct DLChain *c;
    unsigned long *p;
    struct DLPkt *t;
    unsigned long x;

    c = &((struct DLChain *)D_kernel_bss_1EAD8.buf[D_kernel_bss_1EAD8.workBufId])[slot];
    p = (unsigned long *)D_kernel_bss_1EAD8.packet;
    D_kernel_bss_1EAD8.packet += 0x20;
    __asm__ __volatile__("pref 0, 0x40(%0)" : : "r"(p));
    p[0] = ((unsigned long)addr << 32) | 0x50000000;
    ((int *)p)[7] = 0;
    ((int *)p)[6] = 0;
    ((int *)p)[3] = 0;
    ((int *)p)[2] = 0;
    x = ((struct DLPkt *)c->tail)->tag.addr; __asm__("" : "+r"(x)); p[2] = ((unsigned long)(int)x << 32) | 0x20000000;
    ((struct DLPkt *)c->tail)->tag.addr = (unsigned int)p;
    c->tail = (unsigned int)p;
}
