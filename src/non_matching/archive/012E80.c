/* ARCHIVED (Session 63, 2026-10-24): codegen-tuned attempt for 012E80,
 * kept as the matching reference (it is the closest C form: see the STATUS
 * below).  The build now uses src/cod/012E80.c, an instruction-stream
 * transcription; the readable reconstruction is
 * src/non_matching/012E80.c.
 */
/* STATUS (Session 47, 2026-10-22): NON_MATCHING. best score 18 (was 24; sw.py diff lines).
 * Copy loop rewritten from the image register map: an explicit source pointer (pktbuf = header, walked as *pktbuf++) gives the image's move a2,a3 before the sb (a loop.c giv init would land after the blez), packet[i] indexed as the destination giv (move v1,sp after the blez), a separate pktquads behind an empty asm "+r" (blocks nonzero_bits, so the guard stays blez instead of beqz) and the reversed counter copy in the blez slot; an asm volatile "r"(i) use before the loop (no code; i is still uninitialised there) fixes header -> a3. Residual: size/pktquads land in a0/v0 (image: both a1) with the counter in a1 (image: a0), and the size+30 addiu issues after the slt. Tried: size reuse, counter/pktquads live after the loop, division spellings, statement-order grids (96+240+312), two fence-grid levels.
 * Copy loop counts up (for i = 0; i < size; i++) with the quad count reusing size (size = (size + 15) / 16): loop.c reverses it to the image's bnez/blez shape. Dispatch v0/v1 roles fixed: the handler entry goes through an untied empty asm ("=r"(h) : "r"(&tbl[id])) so it is a local pseudo dying where the gp value is loaded (gp value -> v1, table reload -> v0); the old "r"(header) fence removed. Residual: copy prologue registers (image: header a3 with a separate a2 source copy made before the sb, size/quads in a1, count copy a0 in the blez slot; ours keeps header=a1 as the source and size in a0). Tried: statement orders of quads/sb/pktbuf, opaque pktbuf copy, asm on pktquads/size.
 * STATUS (Session 44, 2026-10-21): NON_MATCHING. best score 34 (was 38; sw.py diff lines).
 * isceSifSetDChain declared int (its return value lands in v0, so the cid reload after it takes v1 like the image). Residual: the copy-loop counter/pktquads copy (image: for-loop reversal with blez guard) and the gp/handler-base v0/v1 roles inside the set_gp paths; a 108-variant fence grid gave no gain.
 * Copy loop as for (i = pktquads; i > 0; i--) *d++ = *s++ with s = header gives the image's blez guard; plus the best fence of a 364-variant grid. Residual: sra/srl of the quad count and the a1/a2 copy roles.
 * SCE sifcmd interrupt handler (_SifCmdIntHandler): copy loop, isceSifSetDChain, system/user
 * dispatch on the handler $gp (static inline set_gp as 011CA8). Evidence: cid is reloaded three
 * times and the bgez slot stays nop, so the header is read through a volatile pointer; frame 0xA0
 * means packet[7]. Residuals: the copy source is a copy of the header register and the loop guard
 * is blez (ours beqz, no copy); handler-table registers v0/v1 swapped. Tried loop shapes
 * (for/while/if+while/pointer walk), non-volatile header for the copy part, psize & 0xff.
 * The original .s stays in the build (asm/cod/012E80.s); this C
 * draft (Session 38) is kept for the record. */
/* asm/cod/012E80.s -> func_00112E80.
 * SCE sifcmd interrupt handler (_SifCmdIntHandler): copy the received packet
 * out of the EE receive buffer, re-arm the DMA chain, then dispatch the system
 * (cid bit 31) or user command handler on that handler's own $gp.
 */
typedef unsigned int u128 __attribute__ ((mode (TI)));

struct SifCmdHeader {
    unsigned int psize:8;       /* 0x00 packet size */
    unsigned int dsize:24;
    void *dest;                 /* 0x04 */
    int cid;                    /* 0x08 */
    unsigned int opt;           /* 0x0C */
};

struct SifCmdHandler {          /* 12 bytes */
    void (*handler)(void *, void *);    /* 0x00 */
    void *harg;                 /* 0x04 */
    int gp;                     /* 0x08 the handler's $gp */
};

struct SifCmdData {             /* D_0014B358 (sceSifGetDataTable) */
    void *pktbuf;               /* 0x00 */
    void *unused;               /* 0x04 */
    void *iopbuf;               /* 0x08 */
    struct SifCmdHandler *sys_cmd_handlers;     /* 0x0C */
    int nr_sys_handlers;        /* 0x10 */
    struct SifCmdHandler *usr_cmd_handlers;     /* 0x14 */
    int nr_usr_handlers;        /* 0x18 */
};

extern struct SifCmdData D_0014B358;

int isceSifSetDChain(void);

/* old = $gp, $gp = new (as in sceSifExecNotifyHandler 011CA8) */
static __inline__ int set_gp(int gp)
{
    int old;
    __asm__ __volatile__ ("move %0, $gp\n\tmove $gp, %1" : "=&r" (old) : "r" (gp) : "memory");
    return old;
}

int func_00112E80(void) {
    u128 packet[7];
    u128 *pktbuf;
    struct SifCmdData *cmd = &D_0014B358;
    volatile struct SifCmdHeader *header;
    void (*handler)(void *, void *);
    int size, pktquads, id, i, gp;

    header = (volatile struct SifCmdHeader *)cmd->pktbuf;
    if (!(size = header->psize))
        return 0;
    header->psize = 0;
    pktbuf = (u128 *)header;
    pktquads = (size + 15) / 16;
    asm volatile("" : : "r"(i));
    asm("" : "+r"(pktquads));
    for (i = 0; i < pktquads; i++)
        packet[i] = *pktbuf++;

    isceSifSetDChain();

    header = (volatile struct SifCmdHeader *)packet;
    if (header->cid < 0) {
        id = header->cid & 0x7FFFFFFF;
        if (id < cmd->nr_sys_handlers) {
            handler = cmd->sys_cmd_handlers[id].handler;
            if (handler) {
                struct SifCmdHandler *h;
                asm("" : "=r"(h) : "r"(&cmd->sys_cmd_handlers[id]));
                gp = set_gp(h->gp);
                handler(packet, cmd->sys_cmd_handlers[id].harg);
                set_gp(gp);
            }
        }
    } else {
        id = header->cid;
        if (id < cmd->nr_usr_handlers) {
            handler = cmd->usr_cmd_handlers[id].handler;
            if (handler) {
                struct SifCmdHandler *h;
                asm("" : "=r"(h) : "r"(&cmd->usr_cmd_handlers[id]));
                gp = set_gp(h->gp);
                handler(packet, cmd->usr_cmd_handlers[id].harg);
                set_gp(gp);
            }
        }
    }
    __asm__ __volatile__ ("sync" ::: "memory");
    __asm__ __volatile__ ("ei");
    return 0;
}
