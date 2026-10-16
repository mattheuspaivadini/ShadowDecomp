/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 82 [cc=29].
 * R3 famD: name copy + 0x24 struct reply copy
 * The original .s stays in the build (asm/cod/017288.s); this C
 * draft (Session 8) is kept for the record. */
int _sceCdInitSema(void);
int PollSema(int a0);
void SignalSema(int a0);
int sceCdSync(int a0);
void sceSifInitRpc(int a0);
int sceSifBindRpc(int a0, int a1, int a2);
int scePrintf(const char *msg, ...);
int sceSifWriteBackDCache(int a0, int a1);
int sceSifCallRpc(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);

extern int _sceCd_ncmd_semid[];    /* lui/%lo (non-small) */
extern int D_00133A5C[];    /* lui/%lo */
extern int D_00133A8C[];    /* lui/%lo */
extern int SCE_CD_debug[];    /* lui/%lo */
extern char D_001388F0[];   /* lui/addiu */
extern char D_00138910[];   /* lui/addiu */
extern char D_00138928[];   /* lui/addiu */
extern char D_00138938[];   /* lui/addiu */
extern char D_00138948[];   /* lui/addiu */
extern char D_00150EA4[];   /* lui/addiu, argument for the trace print */
extern char D_00151000[];   /* lui/addiu, command object */
extern char D_00150E80[];   /* lui/addiu, request block   */
extern char D_00150FC0[];   /* lui/addiu, reply block     */

struct R17288 {             /* the 0x24-byte reply record */
    unsigned int w[9];      /* 0x24 bytes */
};

int sceCdLayerSearchFile(int a0, int a1, int a2) {
    int i;
    int c;
    int r;
    char *p;
    char *s2;

    _sceCdInitSema();
    if (_sceCd_ncmd_semid[0] != PollSema(_sceCd_ncmd_semid[0]))
        return 0;
    D_00133A5C[0] = 1;
    if (sceCdSync(1) != 0)
        goto fail;
    sceSifInitRpc(0);
    if (D_00133A8C[0] < 0) {
        for (;;) {
            if (sceSifBindRpc((int)D_00151000, 0x80000597, 0) < 0) {
                if (SCE_CD_debug[0] > 0)
                    scePrintf(D_001388F0);
                i = 0x100000;
                while (i != -1) {
                    i--;
                    __asm__ __volatile__ ("nop\n\tnop\n\tnop\n\tnop");
                }
                continue;
            }
            if (D_00151000[9] != 0) {
                D_00133A8C[0] = 0;
                break;
            }
            i = 0x100000;
            while (i != -1) {
                i--;
                __asm__ __volatile__ ("nop\n\tnop\n\tnop\n\tnop");
            }
        }
    }
    p = D_00150E80;
    s2 = (char *)a1;
    p[0x24] = s2[0];
    i = 0;
    if (s2[0] != 0) {
        for (i = 1; i < 0x100; i++) {
            c = s2[i];
            p[0x24 + i] = c;
            if (c == 0)
                break;
        }
    }
    if (i == 0x100)
        p[0x123] = 0;
    if (SCE_CD_debug[0] > 0)
        scePrintf(D_00138910, (int)D_00150EA4);
    *(int *)(p + 0x128) = a2;
    *(int *)(p + 0x124) = (int)p;
    sceSifWriteBackDCache((int)p, 0x12C);
    if (sceSifCallRpc((int)D_00151000, 0, 0, (int)p, 0x12C,
                      (int)D_00150FC0, 4, 0, 0) < 0) {
    fail:
        SignalSema(_sceCd_ncmd_semid[0]);
        return 0;
    }
    *(struct R17288 *)a0 =
        *(struct R17288 *)(((int)D_00150E80) | 0x20000000);
    if (SCE_CD_debug[0] > 0)
        scePrintf(D_00138928, (int)a0 + 8);
    if (SCE_CD_debug[0] > 0)
        scePrintf(D_00138938, *(int *)((int)a0 + 4));
    if (SCE_CD_debug[0] > 0)
        scePrintf(D_00138948, *(int *)((int)a0 + 0));
    r = *(int *)(((int)D_00150FC0) | 0x20000000);
    SignalSema(_sceCd_ncmd_semid[0]);
    return r;
}
