/* asm/cod/0092F8.s -> func_001092F8.
 * SCE sifrpc request-end handler (_request_end): the end_function runs on the
 * caller's $gp (cd->f18), swapped in and out by a two-move asm.
 * MATCHED. */
struct RpcEnd {             /* the rend packet */
    char pad00[0x1C];
    struct RpcCd *cd;       /* 0x1C client data */
    unsigned int cid;       /* 0x20 command id */
    int  server;            /* 0x24 */
    int  buf;               /* 0x28 */
};

struct RpcCd {              /* SifRpcClientData */
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
};

int iSignalSema(int sema);
int func_00109268(int a0);

/* old = $gp; $gp = new. The memory clobber is read off the image: end_function
   and end_param are reloaded after the swap. (UNCONFIRMED: the SDK macro's name.) */
#define SET_GP(old, new) __asm__ __volatile__ ("move %0, $gp\n\tmove $gp, %1" : "=&r" (old) : "r" (new) : "memory")

void func_001092F8(struct RpcEnd *pkt) {
    struct RpcCd *cd;
    int gp, tmp;

    switch (pkt->cid) {
    case 0x8000000A:
        cd = pkt->cd;
        if (cd->f1C) {
            SET_GP(gp, cd->f18);
            cd->f1C(cd->f20);
            SET_GP(tmp, gp);
        }
        break;
    case 0x8000000C:    /* UNCONFIRMED: a third, empty case above 0x8000000A is what makes the
                           switch tree test 0x8000000A first; the RDATA id is a guess */
        break;
    case 0x80000009:
        cd = pkt->cd;
        cd->f24 = pkt->server;
        cd->f14 = pkt->buf;
        break;
    }
    cd = pkt->cd;
    if (cd->f08 >= 0)
        iSignalSema(cd->f08);
    func_00109268(cd->f00);
    cd->f00 = 0;
}
