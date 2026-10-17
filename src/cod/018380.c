/* asm/cod/018380.s -> func_00118380.
 * sceSifMCallRpc size-check wrapper; aligned sizes in fresh locals n/m change the sreg allocation (Session 20)
 * MATCHED. */
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
    int n, m;
    n = (ssize + 0x3F) & -0x40;
    m = (rsize + 0x3F) & -0x40;
    bufsize = cd->bufsize;
    if (bufsize < n || bufsize < m) {
        scePrintf(D_00138AC0);
        scePrintf(D_00138AF8, fno, n, m, bufsize);
        return -0x21F;
    }
    return sceSifMCallRpc(cd, fno, 0, buf, n, buf, m, 0, 0);
}
