/* asm/cod/0097A0.s -> sceSifBindRpc.
 * SCE sifrpc bind (cmd 0x80000009); same typed structs as sceSifCallRpc 009980; rpc_id load before the packet store
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
    int  f0C;
    int  f10;               /* 0x10 */
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
extern char D_00137EB8[];   /* .rodata: the semaphore name -> lui/%lo */

int func_001091C0(int a0);
int CreateSema(int a0);
int DeleteSema(int a0);
int WaitSema(int a0);
int func_00109268(int a0);
int sceSifWriteBackDCache(int a0, int a1);
int sceSifSendCmd(int a0, int a1, int a2, int a3, int a4, int a5);

int sceSifBindRpc(int a0, int a1, int a2) {
    struct RpcCd *cd;
    struct RpcCall *call;
    struct EESema sema;

    cd = (struct RpcCd *)a0;
    cd->f10 = 0;
    cd->f24 = 0;
    call = (struct RpcCall *)func_001091C0((int)D_00145940);
    if (call == 0)
        return -1;
    cd->f04 = call->f18;
    cd->f00 = (int)call;
    call->f20 = a1;
    call->f14 = (int)call;
    call->f1C = (int)cd;

    if (!(a2 & 1)) {
        sema.max_count = 1;
        sema.option = (int)D_00137EB8;
        sema.init_count = 0;
        cd->f08 = CreateSema((int)&sema);
        if (cd->f08 < 0) {
            func_00109268((int)call);
            return -3;
        }
        if (sceSifSendCmd(0x80000009, (int)call, 0x40, 0, 0, 0) == 0) {
            func_00109268((int)call);
            DeleteSema(cd->f08);
            return -2;
        }
        WaitSema(cd->f08);
        DeleteSema(cd->f08);
        return 0;
    }
    cd->f08 = -1;
    if (sceSifSendCmd(0x80000009, (int)call, 0x40, 0, 0, 0) == 0) {
        func_00109268((int)call);
        return -2;
    }
    return 0;
}
