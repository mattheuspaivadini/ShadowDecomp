/* asm/cod/009980.s -> sceSifCallRpc.
 * sceSifCallRpc; client field int + server load before the client store (TBAA) (Session 23)
 * MATCHED. */
struct RpcCd;
struct RpcCall {            /* the 0x40-byte packet returned by func_001091C0 */
    char pad00[0x14];
    int  f14;               /* 0x14 self pointer */
    int f18;
    int  f1C;               /* 0x1C client data (cd) */
    int  f20;               /* 0x20 rpc_number */
    int  f24;               /* 0x24 send_size */
    int  f28;               /* 0x28 recvbuf */
    int  f2C;               /* 0x2C recv_size */
    int  f30;               /* 0x30 rmode */
    int  f34;               /* 0x34 the server data */
};

struct RpcCd {              /* the caller's SifRpcClientData */
    int  f00;               /* 0x00 the packet */
    int  f04;               /* 0x04 rpc_id */
    int  f08;               /* 0x08 sema_id */
    char pad0C[0x08];
    int  f14;               /* 0x14 buf (the send destination) */
    int  f18;               /* 0x18 the caller's $gp */
    int  f1C;               /* 0x1C end_function */
    void * f20;
    int f24;                /* 0x24 server */
};

struct EESema {
    int count;              /* 0x00 */
    int max_count;          /* 0x04 */
    int init_count;         /* 0x08 */
    int wait;               /* 0x0C */
    int attr;               /* 0x10 */
    int option;             /* 0x14 */
};

extern int D_00145940[16];  /* .bss 0x00145940, 0x40 bytes -> lui/%lo */
extern char D_00137EC8[];   /* .rodata: the semaphore name -> lui/%lo */

int func_001091C0(int a0);
int CreateSema(int a0);
int DeleteSema(int a0);
int WaitSema(int a0);
int func_00109268(int a0);
int sceSifWriteBackDCache(int a0, int a1);
int sceSifSendCmd(int a0, int a1, int a2, int a3, int a4, int a5);

int sceSifCallRpc(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8) {
    struct RpcCd *cd;
    struct RpcCall *call;
    struct EESema sema;
    int gp;

    cd = (struct RpcCd *)a0;
    call = (struct RpcCall *)func_001091C0((int)D_00145940);
    if (call == 0)
        return -1;
    cd->f20 = a8;
    cd->f04 = call->f18;
    cd->f00 = (int)call;
    cd->f1C = a7;
    __asm__ __volatile__("move %0, $28" : "=r"(gp));
    cd->f18 = gp;
    call->f20 = a1;
    call->f24 = a4;
    call->f28 = a5;
    call->f2C = a6;
    call->f14 = (int)call;
    call->f34 = cd->f24;
    call->f1C = (int)cd;

    if (!(a2 & 2)) {
        if (a3 == a5) {
            sceSifWriteBackDCache(a3, a4 < a6 ? a6 : a4);
        } else {
            if (a4 > 0)
                sceSifWriteBackDCache(a3, a4);
            if (a6 > 0)
                sceSifWriteBackDCache(a5, a6);
        }
    }

    if (a2 & 1) {
        if (a7 == 0)
            call->f30 = 0;
        else
            call->f30 = 1;
        cd->f08 = -1;
        if (sceSifSendCmd(0x8000000A, (int)call, 0x40, a3, cd->f14, a4) != 0)
            return 0;
        func_00109268((int)call);
        return -2;
    }

    sema.init_count = 0;
    sema.option = (int)D_00137EC8;
    sema.max_count = 1;
    cd->f08 = CreateSema((int)&sema);
    if (cd->f08 < 0) {
        func_00109268((int)call);
        return -3;
    }
    call->f30 = 1;
    if (sceSifSendCmd(0x8000000A, (int)call, 0x40, a3, cd->f14, a4) == 0) {
        DeleteSema(cd->f08);
        func_00109268((int)call);
        return -2;
    }
    WaitSema(cd->f08);
    DeleteSema(cd->f08);
    return 0;
}
