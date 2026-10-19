/* STATUS (Session 35, 2026-10-19): NON_MATCHING. best score 296 [cc=29].
 * SIF fileio receive callback: 0x440-byte uncached slot, header copy, per-command fix-ups
 * (jtbl_00137F00), queue release or iSignalSema. Residual = the header copy: the original moves it
 * as four lwl/lwr+swl/swr words, ours as two ldl/sdl (32 bytes short). Tried: struct assignment,
 * memcpy call, packed header, field-wise copy, cc=296/dtls/990721.
 * The original .s stays in the build (asm/cod/00A388.s); this C
 * draft (Session 35) is kept for the record. */
struct RecvHdr {                /* head of each 0x440-byte receive slot */
    int sema;                   /* 0x00: < 0 -> queued async request */
    int cmd;                    /* 0x04 */
    void *dst;                  /* 0x08 */
    int size;                   /* 0x0C */
};

struct ReadFix {                /* cmd 2: unaligned head/tail bytes of a read */
    int n1;                     /* 0x14 */
    int n2;                     /* 0x18 */
    char *dst1;                 /* 0x1C */
    char *dst2;                 /* 0x20 */
    char buf1[0x40];            /* 0x24 */
    char buf2[0x40];            /* 0x64 */
};

struct RpcData { int f00; int f04; int f08; int f0C; };

extern int D_00132310 __attribute__((section(".data")));
extern int D_00132318 __attribute__((section(".data")));
extern int _sceFs_q[32];
extern char D_00146640[];
void *func_0012821C(void *dst, const void *src, unsigned int size);   /* memcpy */
int iSignalSema(int sema);

void func_0010A388(struct RpcData *rd)
{
    struct RecvHdr hdr;
    char *ptr;
    unsigned int len;
    char *p, *u;
    struct ReadFix *r;
    int idx, i;

    idx = 0;
    if (D_00132318 != 0)
        idx = rd->f0C;
    D_00132310 = idx;
    p = (char *)((unsigned int)&D_00146640[idx * 0x440] | 0x20000000);
    __builtin_memcpy(&hdr, p, sizeof(hdr));
    if (hdr.sema >= 0)
        func_0012821C(hdr.dst, p + 0x10, hdr.size);
    switch (hdr.cmd) {
    case 2:
        r = (struct ReadFix *)(p + 0x14);
        if (r->n1 > 0) {
            u = (char *)((unsigned int)r->dst1 | 0x20000000);
            for (i = 0; i < r->n1; i++) {
                u[i] = r->buf1[i];
                r->dst1[i] = r->buf1[i];
            }
        }
        if (r->n2 > 0) {
            u = (char *)((unsigned int)r->dst2 | 0x20000000);
            for (i = 0; i < r->n2; i++) {
                u[i] = r->buf2[i];
                r->dst2[i] = r->buf2[i];
            }
        }
        break;
    case 11:
        if (*(int *)hdr.dst > 0) {
            __builtin_memcpy(&ptr, p + 0x14, 4);
            __builtin_memcpy(ptr, p + 0x18, 0x144);
        }
        break;
    case 12:
        __builtin_memcpy(&ptr, p + 0x14, 4);
        __builtin_memcpy(ptr, p + 0x18, 0x40);
        break;
    case 23:
    case 25:
    case 26:
        __builtin_memcpy(&ptr, p + 0x14, 4);
        __builtin_memcpy(&len, p + 0x18, 4);
        if (len > 0x400)
            len = 0x400;
        func_0012821C(ptr, p + 0x1C, len);
        break;
    }
    if (hdr.sema < 0) {
        hdr.sema = -hdr.sema;
        for (i = 0; i < 32; i++) {
            if (_sceFs_q[i] == hdr.sema) {
                _sceFs_q[i] = -1;
                break;
            }
        }
    } else
        iSignalSema(hdr.sema);
}
