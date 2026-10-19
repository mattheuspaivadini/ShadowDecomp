/* asm/cod/0013C8.s -> func_001013C8.
 * loader: read the module-info file (name line + stack size parsed after the first ' '); buf pointer local keeps moduleInfo in one register
 * MATCHED. */
struct LoaderModuleInfo {
    char name[0x40];            /* 0x00 module line read from the file */
    int  stack_size;            /* 0x40 UNCONFIRMED: default 0x4000, parsed after the first ' ' */
    int  w44;                   /* 0x44 */
};

struct LoaderStat {             /* sce_stat */
    unsigned int mode;          /* 0x00 */
    unsigned int attr;          /* 0x04 */
    unsigned int size;          /* 0x08 */
    unsigned char ctime[8];     /* 0x0C */
    unsigned char atime[8];     /* 0x14 */
    unsigned char mtime[8];     /* 0x1C */
    unsigned int hisize;        /* 0x24 */
    unsigned int private_[6];   /* 0x28 */
};

extern struct LoaderModuleInfo moduleInfo;
extern char D_001364D0[];
extern char D_00139E60[];

int LoaderSysGetstat(const char *path, struct LoaderStat *st);
int LoaderSysFOpen(const char *path, int mode, int perm);
int LoaderSysFRead(int fd, void *buf, int size);
int LoaderSysFClose(int fd);
void PutStringS(int color, const char *fmt, ...);
int sscanf(const char *s, const char *fmt, ...);

struct LoaderModuleInfo *func_001013C8(const char *path) {
    struct LoaderStat st;
    unsigned long size;
    int i;
    int fd;
    char *p;
    char *buf;

    buf = moduleInfo.name;
    moduleInfo.stack_size = 0x4000;
    fd = LoaderSysGetstat(path, &st);
    if (fd != 0) {
        PutStringS(0xFF804000, D_001364D0, path, fd);
        return 0;
    }
    fd = LoaderSysFOpen(path, 1, 0);
    if (fd < 0) {
        moduleInfo.name[0] = 0;
        PutStringS(0xFF804000, D_001364D0, path, fd);
        return 0;
    }
    size = ((unsigned long)st.hisize << 32) | st.size;
    LoaderSysFRead(fd, buf, size);
    LoaderSysFClose(fd);
    buf[(int)size] = 0;
    buf[0x3F] = 0;
    for (i = 0; i < size; i++) {
        p = &buf[i];
        if (*p == ' ') {
            *p = 0;
            sscanf(p + 1, D_00139E60, &moduleInfo.stack_size);
            break;
        }
    }
    return &moduleInfo;
}
