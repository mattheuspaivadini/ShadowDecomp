/* KERNEL.XFF @ 0x01AEF8 (184 B) - isysInitObjSystem   [MATCH: -G0 -fno-strict-aliasing]
 * Evidence: memset(.bss+0x27100, 0, 0x52080) clears the 14000-entry 0x18-byte
 * object pool (14000*0x18 = 0x52080); two word clears at .bss+0x79184/0x79188;
 * then the free-list link `p->next = (p + 1) - pool` for entries 0..0x36AE
 * (the image keeps a 64-bit-free 32-bit `(offset+0x18)>>3 * 0xAAAAAAAB` because
 * the 16-bit field truncates the pointer difference -- the same getIdx idiom as
 * the matched 0x0197E8/0x01AFB0 pair).  `next` is the 16-bit index at +0x0E
 * (see 01AFB0.c/01B048.c).  After the loop: head .bss+0x79180 = &pool[1] and
 * .bss+0x7918C = iosCreateSema(1, 1, 0) (args materialised in a0/a1/a2, store
 * parked in the jal delay slot by the scheduler).  UNCONFIRMED: struct names.
 * Lever: an ASCENDING index loop `i = 0; i <= 0x36AE; i++` with the ternary
 * getIdx macro -- the image's descending counter + separate byte-offset IV is
 * what the scheduler/IV code makes of it.
 */
struct IsysGroup { unsigned short first; unsigned short last; };
struct GroupEnt {
    void *obj;
    struct IsysGroup *group;
    int param;
    unsigned char lock;
    char padD;
    unsigned short next;
    unsigned short prev;
    unsigned short onext;
    unsigned short oprev;
    unsigned short link;
};
extern struct GroupEnt D_kernel_bss_27100[];
extern struct GroupEnt *D_kernel_bss_79180;
extern int D_kernel_bss_79184;
extern int D_kernel_bss_79188;
extern int D_kernel_bss_7918C;
void *memset(void *p, int c, unsigned int n);
int iosCreateSema(int a, int b, int c);
#define getIdx(e) ((e) ? (e) - D_kernel_bss_27100 : 0)

void isysInitObjSystem(void) {
    int i;
    int k;

    D_kernel_bss_79184 = 0;
    D_kernel_bss_79188 = 0;
    memset(D_kernel_bss_27100, 0, 0x52080);
    for (i = 0, k = 0x36AE; i <= 0x36AE; i++) {
        D_kernel_bss_27100[i].next = getIdx(&D_kernel_bss_27100[i + 1]);
    }

    D_kernel_bss_79180 = &D_kernel_bss_27100[1];
    D_kernel_bss_7918C = iosCreateSema(1, 1, 0);
}
