/* STATUS (10, 2026-10-16): NON_MATCHING. best score 13 [cc=29].
 * 
 * The original .s stays in the build (asm/cod/018380.s); this C
 * draft (10) is kept for the record. */
typedef struct {
    int pad[12];
    int bufsize;
} SifClientData;

extern int scePrintf(const char *fmt, ...);
extern int sceSifMCallRpc(void *cd, unsigned int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end_func, void *end_param);

extern const char D_00138AC0[];
extern const char D_00138AF8[];

int func_00118380(SifClientData *cd, int fno, void *buf, int ssize, int rsize) {
    int bufsize;

    ssize = (ssize + 0x3F) & -0x40;
    rsize = (rsize + 0x3F) & -0x40;
    bufsize = cd->bufsize;
    if (bufsize < ssize || bufsize < rsize) {
        scePrintf(D_00138AC0);
        scePrintf(D_00138AF8, fno, ssize, rsize, bufsize);
        return -0x21F;
    }
    return sceSifMCallRpc(cd, fno, 0, buf, ssize, buf, rsize, 0, 0);
}
