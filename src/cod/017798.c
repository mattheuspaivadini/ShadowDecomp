/* asm/cod/017798.s -> sceCdSync.
 * Non-blocking path as one || test returning 1 / 0: two separate ifs let combine fold the second into sltu (Session 28).
 * MATCHED. */
extern __attribute__((section(".data"))) int SCE_CD_debug;
extern __attribute__((section(".data"))) int _sceCd_c_cb_sem;
extern int _sceCd_cd_ncmd[];
extern char D_001389A0[];

void scePrintf(const char *fmt, ...);
int DelayThread(int usec);
int sceSifCheckStatRpc(int *cd);

int sceCdSync(int mode) {
    if (mode == 0) {
        if (SCE_CD_debug > 0)
            scePrintf(D_001389A0);
        while (_sceCd_c_cb_sem != 0 || sceSifCheckStatRpc(_sceCd_cd_ncmd) != 0)
            DelayThread(4000);
        return 0;
    }
    if (_sceCd_c_cb_sem != 0 || sceSifCheckStatRpc(_sceCd_cd_ncmd) != 0)
        return 1;
    return 0;
}
