/* ARCHIVED (Session 63, 2026-10-24): codegen-tuned attempt for 00A388,
 * kept as the matching reference (it is the closest C form: see the STATUS
 * below).  The build now uses src/cod/00A388.c, an instruction-stream
 * transcription; the readable reconstruction is
 * src/non_matching/equiv/00A388.c.
 */
/* STATUS (Session 62, 2026-10-23): NON_MATCHING, still 2 diff instructions.
 * REA/Ghidra dossier ev_fed12ce2efc901b492f2597a4f6b1f94d7024917bcfa486b40df6c77016c4ba8
 * re-read. The sched2 dump of the entry block shows why the store cannot move
 * earlier: insn 42 (`sw a1,0(v0)` = D_00132310) depends on insn 37, the
 * asm("" : "+r"(idx)) bracket, and 37 has REG_DEP_ANTI on the mult (both
 * write/read a1), so the store can only issue at t=4 while the %lo addiu of
 * D_00146640 (insn 29, no dependency) issues at t=3. Removing the WAR with an
 * input-only asm ("r"(idx)) lets the store issue earlier but breaks the global
 * allocation the bracket exists for: the case blocks reallocate and the
 * function is 8 bytes short (940 B). Moving the store or the bracket around
 * `p = ...` is equally fatal (940 B); only the current order keeps 948 B.
 * STATUS (Session 46, 2026-10-22): NON_MATCHING. best score 2 (was 296; sw.py diff lines).
 * Header copied as four 4-byte __builtin_memcpy calls (each expands to lwl/lwr+swl/swr; one 16-byte copy gives ldl/sdl); byte loops keep the destination in a local (d = r->dst1) and store u[i] then d[i] from one load (d[i] = u[i] = r->buf1[i]); the search loop compares against a copy (idx = hdr.sema; asm "+r") with an "m"(_sceFs_q[0]) fence first and a volatile -1 store (keeps it out of the b slot). An empty asm "+r"(idx) between the slot address and the D_00132310 store fixes the global allocation (idx -> a1; without it every case block reallocates). Residual: that asm costs sched2 one cycle, so the D_00132310 sw issues after addiu %lo(D_00146640) (image: before). Tried: asm before/after the store, untied asm, volatile store, barrier/"m" fence grids (1728), other compilers.
 * Session 61 (2026-10-23): REA-imported Ghidra dossier ev_fed12ce2efc901b492f2597a4f6b1f94d7024917bcfa486b40df6c77016c4ba8 confirms the receive-slot selection and queue logic; the target assembly stores D_00132310 before the low-half addiu for D_00146640. Freshly staged cc=29 trials (pinned $a0 lui/addiu around the store, an offset temporary with a +r fence, and moving the store ahead of pointer formation) scored 38, 77, and 40; restored the baseline draft (score 2). The full 29/296/2.95 matrix and the Ghidra pseudocode did not yield a match.
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
    char *p, *u, *d;
    unsigned char c;
    struct ReadFix *r;
    int idx, i;

    idx = 0;
    if (D_00132318 != 0)
        idx = rd->f0C;
    p = (char *)((unsigned int)&D_00146640[idx * 0x440] | 0x20000000);
    asm("" : "+r"(idx));
    D_00132310 = idx;
    __builtin_memcpy(&hdr.sema, p, 4);
    __builtin_memcpy(&hdr.cmd, p + 4, 4);
    __builtin_memcpy(&hdr.dst, p + 8, 4);
    __builtin_memcpy(&hdr.size, p + 12, 4);
    if (hdr.sema >= 0)
        func_0012821C(hdr.dst, p + 0x10, hdr.size);
    switch (hdr.cmd) {
    case 2:
        r = (struct ReadFix *)(p + 0x14);
        if (r->n1 > 0) {
            d = r->dst1;
            u = (char *)((unsigned int)d | 0x20000000);
            for (i = 0; i < r->n1; i++) {
                d[i] = u[i] = r->buf1[i];
            }
        }
        if (r->n2 > 0) {
            d = r->dst2;
            u = (char *)((unsigned int)d | 0x20000000);
            for (i = 0; i < r->n2; i++) {
                d[i] = u[i] = r->buf2[i];
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
        __asm__ __volatile__ ("" : : "m" (_sceFs_q[0]));
        hdr.sema = -hdr.sema;
        idx = hdr.sema;
        asm("" : "+r"(idx));
        for (i = 0; i < 32; i++) {
            if (_sceFs_q[i] == idx) {
                *(volatile int *)&_sceFs_q[i] = -1;
                break;
            }
        }
    } else
        iSignalSema(hdr.sema);
}
