/* C equivalent of func_00112E80 (012E80, 328 B @ 0x00112E80).
 *
 * Reconstructed instruction-by-instruction from asm/cod/012E80.s and the
 * REA/Ghidra Emotion Engine dossier ev_708da75080f0143cd1a09647a24eb8f8e24d64a37063c34eadae4035832381ec
 * (pseudocode cross-checked against the matched SIF helpers sceSifExecNotifyHandler
 * 011CA8 and isceSifSetDChain in src/cod/).  Readable reconstruction: NOT
 * byte-exact (10 diff instructions), not part of the build.  The codegen-tuned
 * near-miss is src/non_matching/012E80.c.
 *
 * SCE sifcmd interrupt handler: copy the packet out of the EE receive buffer,
 * re-arm the DMA chain, then dispatch the system (cid < 0) or user handler with
 * that handler's own $gp loaded.
 *
 * Behaviour derived from the target:
 *   12E9C  lbu/andi 0xFF      -> psize is a byte field of the header
 *   12EB0  blez (size==0)     -> an empty packet is only acknowledged
 *   12EC8  sb zero            -> psize is cleared before the copy
 *   12ED0  blez + bottom test -> for (i = quads; i > 0; i--)
 *   12F00  sync / 12F04 ei    -> interrupt context is re-enabled after the copy
 *   12F08  lw cid twice       -> header is read through a volatile pointer
 *   12F9C  lw a1,4(v0)        -> handler(packet, handler->harg)
 *   12FA0  daddu v0,gp        -> set_gp() returns the previous $gp
 *   12FA8  sync / 12FAC ei    -> at the common exit
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));

struct sif_cmd_header {
    unsigned int psize:8;           /* 0x00 payload size in bytes */
    unsigned int dsize:24;
    void *dest;                     /* 0x04 */
    int cid;                        /* 0x08: bit 31 selects the user table */
    unsigned int opt;               /* 0x0C */
};

struct sif_cmd_handler {            /* 12 bytes */
    void (*handler)(void *, void *);/* 0x00 */
    void *harg;                     /* 0x04 */
    int gp;                         /* 0x08: the handler's $gp */
};

struct sif_cmd_data {               /* D_0014B358 */
    void *pktbuf;                   /* 0x00 */
    void *unused;                   /* 0x04 */
    void *iopbuf;                   /* 0x08 */
    struct sif_cmd_handler *sys_cmd_handlers;   /* 0x0C */
    int nr_sys_handlers;            /* 0x10 */
    struct sif_cmd_handler *usr_cmd_handlers;   /* 0x14 */
    int nr_usr_handlers;            /* 0x18 */
};

extern struct sif_cmd_data D_0014B358;

int isceSifSetDChain(void);

/* old = $gp; $gp = gp (same helper as sceSifExecNotifyHandler 011CA8). */
static __inline__ int set_gp(int gp)
{
    int old;
    __asm__ __volatile__ ("move %0, $gp\n\tmove $gp, %1"
                          : "=&r" (old) : "r" (gp) : "memory");
    return old;
}

int func_00112E80(void)
{
    u_long128 packet[7];            /* 0xA0 frame: 7 quadwords of payload */
    struct sif_cmd_data *cmd = &D_0014B358;
    volatile struct sif_cmd_header *header;
    u_long128 *src, *dst;
    int size, quads, id, i, gp;

    header = (volatile struct sif_cmd_header *)cmd->pktbuf;
    size = header->psize;
    if (size == 0)
        return 0;
    header->psize = 0;

    src = (u_long128 *)header;
    dst = packet;
    for (i = (size + 15) / 16; i > 0; i--)
        *dst++ = *src++;

    isceSifSetDChain();

    header = (volatile struct sif_cmd_header *)packet;
    if (header->cid < 0) {
        id = header->cid & 0x7FFFFFFF;
        if (id < cmd->nr_sys_handlers) {
            struct sif_cmd_handler *h = &cmd->sys_cmd_handlers[id];
            if (h->handler != 0) {
                gp = set_gp(h->gp);
                h->handler(packet, h->harg);
                set_gp(gp);
            }
        }
    } else {
        id = header->cid;
        if (id < cmd->nr_usr_handlers) {
            struct sif_cmd_handler *h = &cmd->usr_cmd_handlers[id];
            if (h->handler != 0) {
                gp = set_gp(h->gp);
                h->handler(packet, h->harg);
                set_gp(gp);
            }
        }
    }
    __asm__ __volatile__ ("sync" ::: "memory");
    __asm__ __volatile__ ("ei");
    return 0;
}
