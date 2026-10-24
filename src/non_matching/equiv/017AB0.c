/* C equivalent of sceCdInit (017AB0, 744 B @ 0x00117AB0).
 *
 * Reconstructed from asm/cod/017AB0.s and the REA/Ghidra Emotion Engine
 * dossier ev_684bdbe4f71bdd3afbcf52d450e957b35c0753fffb5377ef4414446f2b363dec;
 * prototypes follow the matched sceSif* helpers.  Readable reconstruction:
 * NOT byte-exact (40 diff instructions in the .bss/.data %hi priority and the
 * reply-decode temporaries), not part of the build.  The codegen-tuned
 * near-miss is src/non_matching/017AB0.c.
 *
 * sceCdInit: bind the CD/DVD SIF RPC service, read the drive configuration,
 * select the read mode and start the CD semaphores.
 *
 * Behaviour derived from the target:
 *   17AF8  lui s5,%hi(D_00133A9C)  -> init counter, incremented per attempt
 *   17B88  lw 0x24(s1)            -> SifRpcClientData.server (0x24)
 *   17BA8  addiu v1,zero,-1
 *   17BC4  bne v0,v1              -> the retry loop counts down to -1
 *   17BF8  sw zero,0(sp)          -> 9th argument of sceSifCallRpc is 0
 *   17C60  lui a1,0x2000 / or     -> the reply is read through its uncached alias
 *   17CA8  slt/sltu + movn        -> b/256 < 2 || a/256 < 2 selects mode 2
 *   17C98  a2 = -1                -> sign probe for the /256 expansion
 */
struct sif_rpc_client_data {        /* 0x28 bytes */
    int  pad00[9];
    int  server;                    /* 0x24 */
};

extern int SCE_CD_debug;
extern int _sceCd_ncmd_semid;
extern int _sceCd_scmd_semid;
extern int D_00133A60;
extern int D_00133A64;
extern int D_00133A7C;
extern int D_00133A88;
extern int D_00133A8C;
extern int D_00133A90;
extern int D_00133A94;
extern int D_00133A98;
extern int D_00133A9C;
extern int _sceCd_ee_read_mode;
extern int _sceCd_CdInit_ON;
extern struct sif_rpc_client_data D_00151028;
extern int D_00151080;
extern int _sceCd_scmdrdata[];
extern char D_00138A00[];           /* "sceCdInit: bind error %d (retry %d)\n" */
extern char D_00138A20[];           /* "sceCdInit: reinit\n" */

void scePrintf(const char *fmt, ...);
void _sceCdInitSema(void);
int sceCdSyncS(int mode);
void sceSifInitRpc(int mode);
int sceSifBindRpc(struct sif_rpc_client_data *cd, int request, int mode);
void sceSifWriteBackDCache(void *addr, int size);
int sceSifCallRpc(struct sif_rpc_client_data *cd, int rpc, int mode, void *send,
                  int ssize, void *recv, int rsize, void *end, void *param);
void func_00117098(void);           /* UNCONFIRMED: CD command init */
void func_00117210(void);           /* UNCONFIRMED: CD state init */

int sceCdInit(int mode)
{
    int i, r, a, b, c;
    int *rd;

    if (sceCdSyncS(1) != 0)
        return 0;
    sceSifInitRpc(0);

    D_00133A64 = 1;
    D_00133A90 = -1;
    D_00133A8C = -1;
    D_00133A9C++;
    _sceCd_ee_read_mode = 0;
    D_00133A94 = -1;
    D_00133A88 = -1;
    D_00133A7C = -1;
    D_00133A98 = -1;

    for (;;) {
        b = sceSifBindRpc(&D_00151028, 0x80000592, 0);
        if (b < 0) {
            if (SCE_CD_debug > 0)
                scePrintf(D_00138A00, b, D_00133A9C);
            for (i = 0x100000; i != -1; i--)
                ;
            continue;
        }
        if (D_00151028.server != 0) {
            D_00151080 = mode;
            D_00133A98 = 0;
            sceSifWriteBackDCache(&D_00151080, 4);
            rd = _sceCd_scmdrdata;
            if (sceSifCallRpc(&D_00151028, 0, 0, &D_00151080, 4, rd, 0x10,
                              0, 0) < 0) {
                D_00133A64 = 0;
                return 0;
            }
            break;
        }
        for (i = 0x100000; i != -1; i--)
            ;
    }

    /* the reply is copied through its uncached alias */
    c = *(int *)((unsigned int)&rd[3] | 0x20000000);
    b = *(int *)((unsigned int)&rd[1] | 0x20000000);
    a = *(int *)((unsigned int)&rd[2] | 0x20000000);

    r = 1;
    if (c != 0xFF) {
        if (c == 0xFE)
            SCE_CD_debug = 1;
        else if (b / 256 < 2 || a / 256 < 2)
            r = 2;
    }
    D_00133A64 = 0;

    switch (mode) {
    case 5:
        if (SCE_CD_debug > 0)
            scePrintf(D_00138A20);
        func_00117098();
        _sceCd_ncmd_semid = -1;
        _sceCd_scmd_semid = -1;
        D_00133A60 = -1;
        _sceCd_CdInit_ON = 0;
        break;
    case 0:
    case 1:
    default:
        _sceCdInitSema();
        func_00117210();
        _sceCd_CdInit_ON = 1;
        break;
    }
    return r;
}
