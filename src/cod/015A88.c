/* asm/cod/015A88.s -> sceDbcInit.
 * libdbc init: bind loops with an empty busy-wait, module version check, sema + work area; bind-failure block placed inside the sema-failure branch (Session 34)
 * MATCHED. */
typedef struct { int count; int max_count; int init_count; int wait_threads; unsigned int attr; void *option; int pad[2]; } ee_sema_t;
struct SifRpcClientData { char pad00[0x24]; void *server; };

extern int D_00133A28 __attribute__((section(".data")));
extern int D_00150DC0 __attribute__((section(".bss")));
extern struct SifRpcClientData D_0014E900;
extern struct SifRpcClientData D_0014E950;
extern struct SifRpcClientData D_0014E978[2];
extern int D_00150D80[16];
extern char D_00150D00[];
extern char D_001385C0[];
extern char D_001385D8[];
extern char D_00138600[];
extern char D_00138630[];
extern char D_00138640[];

void sceSifInitRpc(int mode);
int sceSifBindRpc(struct SifRpcClientData *cd, int rpc, int mode);
int func_00115A30(void);
int scePrintf(const char *fmt, ...);
void func_00116C58(const char *fmt, ...);
int CreateSema(ee_sema_t *s);
int sceDbcSetWorkAddr(void *addr);

int sceDbcInit(void) {
    ee_sema_t s;
    int i;
    int v;
    int j;

    if (D_00133A28 == 1)
        return 1;
    D_00150DC0 = 0;
    sceSifInitRpc(0);
    while (1) {
        if (sceSifBindRpc(&D_0014E900, 0x80001300, 0) < 0)
            goto bind_failed;
        if (D_0014E900.server != 0)
            break;
        i = 0x10000;
        while (i--)
            ;
    }
    v = func_00115A30();
    if ((v >> 4) != 0x31) {
        scePrintf(D_001385D8);
        scePrintf(D_00138600, 3, 0x10, v >> 8, v & 0xFF);
        return 0;
    }
    while (1) {
        if (sceSifBindRpc(&D_0014E950, 0x8000131C, 0) < 0)
            goto bind_failed;
        if (D_0014E950.server != 0)
            break;
        i = 0x10000;
        while (i--)
            ;
    }
    for (j = 0; j < 2; j++) {
        while (1) {
            if (sceSifBindRpc(&D_0014E978[j], 0x8000131E + j, 0) < 0)
                goto bind_failed;
            if (D_0014E978[j].server != 0)
                break;
            i = 0x10000;
            while (i--)
                ;
        }
    }
    s.init_count = 1;
    s.max_count = 0x7F;
    s.option = D_00138630;
    D_00150DC0 = CreateSema(&s);
    if (D_00150DC0 < 0) {
        return 0;
    bind_failed:
        func_00116C58(D_001385C0);
        return 0;
    }
    for (i = 15; i >= 0; i--)
        D_00150D80[i] = 0;
    func_00116C58(D_00138640, D_00150D00);
    sceDbcSetWorkAddr(D_00150D00);
    D_00133A28 = 1;
    return 1;
}
