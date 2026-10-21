/* asm/cod/017288.s -> sceCdLayerSearchFile.
 * SCE libcdvd sceCdLayerSearchFile (0175A8 bind template): name copy tests the stored byte, uncached sceCdlFILE result copied with the builtin memcpy, separate wait counter (Session 41)
 * MATCHED. */
struct SifRpcClientData {       /* 0x28 bytes */
    int  pad00[9];
    int  server;                /* 0x24 */
};

typedef struct {
    unsigned int lsn;           /* 0x00 */
    unsigned int size;          /* 0x04 */
    char name[16];              /* 0x08 */
    unsigned char date[8];      /* 0x18 */
    unsigned int flag;          /* 0x20 */
} sceCdlFILE;

struct SearchFileArg {          /* the RPC send block at D_00150E80 */
    sceCdlFILE file;            /* 0x000 */
    char name[256];             /* 0x024 */
    void *addr;                 /* 0x124 */
    int layer;                  /* 0x128 */
};

extern __attribute__((section(".data"))) int SCE_CD_debug;
extern __attribute__((section(".data"))) volatile int _sceCd_ncmd_semid;
extern __attribute__((section(".data"))) int D_00133A5C;
extern __attribute__((section(".data"))) int D_00133A8C;     /* < 0 until the RPC server is bound */
extern struct SifRpcClientData D_00151000;
extern struct SearchFileArg D_00150E80;
extern char D_00150EA4[];       /* D_00150E80.name */
extern int D_00150FC0[];
extern char D_001388F0[];
extern char D_00138910[];
extern char D_00138928[];
extern char D_00138938[];
extern char D_00138948[];

void scePrintf(const char *fmt, ...);
void _sceCdInitSema(void);
int PollSema(int sema);
int SignalSema(int sema);
int sceCdSync(int mode);
void sceSifInitRpc(int mode);
int sceSifBindRpc(struct SifRpcClientData *cd, int request, int mode);
void sceSifWriteBackDCache(void *addr, int size);
int sceSifCallRpc(struct SifRpcClientData *cd, int rpc, int mode, void *send, int ssize, void *recv,
                  int rsize, void *end, void *param);

int sceCdLayerSearchFile(sceCdlFILE *fp, const char *name, int layer) {
    int i;
    int j;
    int r;

    _sceCdInitSema();
    if (_sceCd_ncmd_semid != PollSema(_sceCd_ncmd_semid))
        return 0;
    D_00133A5C = 1;
    if (sceCdSync(1) != 0) {
        SignalSema(_sceCd_ncmd_semid);
        return 0;
    }
    sceSifInitRpc(0);
    if (D_00133A8C < 0) {
        while (1) {
            if (sceSifBindRpc(&D_00151000, 0x80000597, 0) < 0) {
                if (SCE_CD_debug > 0)
                    scePrintf(D_001388F0);
                j = 0x100000;
                while (j--)
                    ;
                continue;
            }
            if (D_00151000.server != 0) {
                D_00133A8C = 0;
                break;
            }
            j = 0x100000;
            while (j--)
                ;
        }
    }
    for (i = 0; i < 256; i++) {
        D_00150E80.name[i] = name[i];
        if (D_00150E80.name[i] == 0)
            break;
    }
    if (i == 256)
        D_00150E80.name[255] = 0;
    if (SCE_CD_debug > 0)
        scePrintf(D_00138910, D_00150EA4);
    D_00150E80.layer = layer;
    D_00150E80.addr = &D_00150E80;
    sceSifWriteBackDCache(&D_00150E80, 0x12C);
    if (sceSifCallRpc(&D_00151000, 0, 0, &D_00150E80, 0x12C, D_00150FC0, 4, 0, 0) < 0) {
        SignalSema(_sceCd_ncmd_semid);
        return 0;
    }
    __builtin_memcpy(fp, (void *)((unsigned int)&D_00150E80 | 0x20000000), sizeof(sceCdlFILE));
    if (SCE_CD_debug > 0)
        scePrintf(D_00138928, fp->name);
    if (SCE_CD_debug > 0)
        scePrintf(D_00138938, fp->size);
    if (SCE_CD_debug > 0)
        scePrintf(D_00138948, fp->lsn);
    r = *(int *)((unsigned int)D_00150FC0 | 0x20000000);
    SignalSema(_sceCd_ncmd_semid);
    return r;
}
