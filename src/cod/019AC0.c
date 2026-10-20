/* asm/cod/019AC0.s -> func_00119AC0.
 * SCE libmrpc request-end handler (the _request_end of 0092F8 for the
 * multi-thread RPC ids 0x80000019..0x8000001D); the end_function runs on the
 * caller's $gp (cd->f18), swapped in and out by a two-move asm.
 * MATCHED. */
struct MRpcEnd {            /* the rend packet */
    char pad00[0x1C];
    struct MRpcCd *cd;      /* 0x1C client data */
    unsigned int cid;       /* 0x20 command id */
    int  server;            /* 0x24 */
    int  buf;               /* 0x28 */
};

struct MRpcCd {             /* the multi-thread SifRpcClientData */
    int  f00;               /* 0x00 the packet */
    int  f04;               /* 0x04 rpc_id */
    int  f08;               /* 0x08 sema_id */
    int  f0C;
    int  f10;
    int  f14;               /* 0x14 buf */
    int  f18;               /* 0x18 the caller's $gp */
    void (*f1C)(void *);    /* 0x1C end_function */
    void *f20;              /* 0x20 end_param */
    int  f24;               /* 0x24 server */
    int  f28;               /* 0x28 the call's semaphore */
    int  f2C;
};

int iSignalSema(int sema);
int func_00119AA0(int a0);

/* old = $gp; $gp = new, as in 0092F8 (memory clobber read off the image) */
#define SET_GP(old, new) __asm__ __volatile__ ("move %0, $gp\n\tmove $gp, %1" : "=&r" (old) : "r" (new) : "memory")

void func_00119AC0(struct MRpcEnd *pkt) {
    struct MRpcCd *cd;
    struct MRpcCd *c;
    int gp, tmp;

    switch (pkt->cid) {
    case 0x8000001A:
        cd = pkt->cd;
        if (cd->f1C) {
            SET_GP(gp, cd->f18);
            cd->f1C(cd->f20);
            SET_GP(tmp, gp);
        }
        iSignalSema(cd->f28);
        break;
    case 0x80000019:
        cd = pkt->cd;
        cd->f24 = pkt->server;
        cd->f14 = pkt->buf;
        iSignalSema(cd->f28);
        break;
    case 0x8000001C:
        break;
    case 0x8000001D:
        cd = pkt->cd;
        cd->f2C = pkt->server;
        iSignalSema(cd->f28);
        break;
    }
    c = pkt->cd;
    if (c->f08 >= 0)
        iSignalSema(c->f08);
    func_00119AA0(c->f00);
    c->f00 = 0;
}
