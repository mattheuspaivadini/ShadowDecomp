/* C equivalent of func_0010A388 (00A388, 948 B @ 0x0010A388).
 *
 * Reconstructed from asm/cod/00A388.s and the REA/Ghidra Emotion Engine
 * dossier ev_fed12ce2efc901b492f2597a4f6b1f94d7024917bcfa486b40df6c77016c4ba8.
 * Readable reconstruction: NOT byte-exact (the D_00132310 store issues one slot
 * after the %lo addiu of D_00146640), not part of the build.  The codegen-tuned
 * near-miss is src/non_matching/00A388.c.
 *
 * SIF file-I/O receive callback.  The IOP deposits each reply in one of the
 * 0x440-byte uncached slots at D_00146640; the callback publishes the slot
 * index, copies the 16-byte header out, runs the command-specific fix-up and
 * then releases the waiting request (queue slot or iSignalSema).
 *
 * Behaviour derived from the target:
 *   10A398  lw/lui D_00132318     -> the port is up: idx = rd->f0C
 *   10A3A0  sw a1,0(v0)           -> D_00132310 = idx
 *   10A3AC  lwl/lwr x4 + swl/swr  -> memcpy(&hdr, p, 16), inlined byte-wise
 *   10A3C8  bltz v0 -> memcpy     -> hdr.sema >= 0: copy the payload out
 *   10A424  addiu a0,v0,-2
 *   10A42C  sltiu a0,0x19         -> switch (hdr.cmd - 2), 25-entry jtbl_00137F00
 *   10A450  case 2                -> two (dst, uncached alias, buf, len) loops
 *   10A4F8  case 0xB              -> if (*(int *)hdr.dst > 0) copy 0x144 bytes
 *   10A5D4  case 0xC              -> copy 0x40 bytes
 *   10A670  case 0x17/0x19/0x1A   -> copy min(p[0x18], 0x400) bytes from p+0x1C
 *   10A6BC  bgez v0               -> sema >= 0: iSignalSema(sema)
 *   10A6C8  lw _sceFs_q, negu     -> else clear queue slot holding -sema
 */
struct rpc_data {                   /* argument block handed in by the SIF RPC */
    int f00;
    int f04;
    int f08;
    int f0C;
};

struct recv_hdr {                   /* 16-byte header at the head of each slot */
    int sema;                       /* 0x00: < 0 -> queued asynchronous request */
    int cmd;                        /* 0x04 */
    void *dst;                      /* 0x08 */
    int size;                       /* 0x0C */
};

struct read_fix {                   /* cmd 2 payload */
    int n1;                         /* 0x14 head piece length */
    int n2;                         /* 0x18 tail piece length */
    char *dst1;                     /* 0x1C */
    char *dst2;                     /* 0x20 */
    char buf1[0x40];                /* 0x24 */
    char buf2[0x40];                /* 0x64 */
};

extern int D_00132310;              /* last serviced slot index */
extern int D_00132318;              /* set once the file system is up */
extern int _sceFs_q[32];            /* pending async request semaphores */
extern char D_00146640[];           /* 0x440-byte receive slots */

void *func_0012821C(void *dst, const void *src, unsigned int size);  /* memcpy */
int iSignalSema(int sema);

void func_0010A388(struct rpc_data *rd)
{
    struct recv_hdr hdr;
    char *p, *u, *d;
    int idx, i;
    struct read_fix *r;

    idx = 0;
    if (D_00132318 != 0)
        idx = rd->f0C;
    p = (char *)((unsigned int)&D_00146640[idx * 0x440] | 0x20000000);
    D_00132310 = idx;

    /* constant size, uncached unaligned source: the compiler emits the four
     * lwl/lwr + swl/swr word copies seen in the image */
    __builtin_memcpy(&hdr, p, sizeof(hdr));

    if (hdr.sema >= 0)
        func_0012821C(hdr.dst, p + 0x10, hdr.size);

    switch (hdr.cmd) {
    case 2:
        r = (struct read_fix *)(p + 0x14);
        if (r->n1 > 0) {
            d = r->dst1;
            u = (char *)((unsigned int)d | 0x20000000);
            for (i = 0; i < r->n1; i++)
                d[i] = u[i] = r->buf1[i];
        }
        if (r->n2 > 0) {
            d = r->dst2;
            u = (char *)((unsigned int)d | 0x20000000);
            for (i = 0; i < r->n2; i++)
                d[i] = u[i] = r->buf2[i];
        }
        break;
    case 0xB:
        /* the destination pointer rides in the payload at p+0x14, and its
         * first word must be positive before the block is copied */
        if (*(int *)hdr.dst > 0)
            __builtin_memcpy(*(void **)(p + 0x14), p + 0x18, 0x144);
        break;
    case 0xC:
        __builtin_memcpy(*(void **)(p + 0x14), p + 0x18, 0x40);
        break;
    case 0x17:
    case 0x19:
    case 0x1A:
        {
            unsigned int len = *(unsigned int *)(p + 0x18);
            if (len > 0x400)
                len = 0x400;
            func_0012821C(*(void **)(p + 0x14), p + 0x1C, len);
        }
        break;
    }

    if (hdr.sema < 0) {
        int sema = -hdr.sema;

        if (_sceFs_q[0] == sema) {
            _sceFs_q[0] = -1;
        } else {
            for (i = 1; i < 32; i++) {
                if (_sceFs_q[i] == sema) {
                    _sceFs_q[i] = -1;
                    break;
                }
            }
        }
    } else {
        iSignalSema(hdr.sema);
    }
}
