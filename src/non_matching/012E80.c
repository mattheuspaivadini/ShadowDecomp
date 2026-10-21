/* STATUS (Session 44, 2026-10-21): NON_MATCHING. best score 34 (was 38; sw.py diff lines).
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
    pktquads = (size + 15) / 16;
    asm volatile("" : : "r"(size));
    header->psize = 0;
    {
        u128 *s = (u128 *)header, *d = packet;
        for (i = pktquads; i > 0; i--)
            *d++ = *s++;
    }

    isceSifSetDChain();

    header = (volatile struct SifCmdHeader *)packet;
    if (header->cid < 0) {
        id = header->cid & 0x7FFFFFFF;
        if (id < cmd->nr_sys_handlers) {
            handler = cmd->sys_cmd_handlers[id].handler;
            asm volatile("" : : "r"(header));
            if (handler) {
                gp = set_gp(cmd->sys_cmd_handlers[id].gp);
                handler(packet, cmd->sys_cmd_handlers[id].harg);
                set_gp(gp);
            }
        }
    } else {
        id = header->cid;
        if (id < cmd->nr_usr_handlers) {
            handler = cmd->usr_cmd_handlers[id].handler;
            if (handler) {
                gp = set_gp(cmd->usr_cmd_handlers[id].gp);
                handler(packet, cmd->usr_cmd_handlers[id].harg);
                set_gp(gp);
            }
        }
    }
    __asm__ __volatile__ ("sync" ::: "memory");
    __asm__ __volatile__ ("ei");
    return 0;
}
