/* asm/cod/002D70.s -> LoaderSysLoadIopModuleFromEEBuffer.
 * LoaderSysLoadIopModuleFromEEBuffer; three static inline helpers (find/setNew/load) at plain -O2 - resolves the -O2/-O3 question, load result taken before the heap free (Session 23)
 * MATCHED. */
typedef struct {
    int w0;
    int w1;
    int w2;
    int w3;
} Block16;

extern int D_0013A008;      /* module count (small data, gp-relative) */
extern char D_0013CB90[];   /* 16-byte module identifier records */
extern char D_00136900[];
extern char D_00136948[];
extern char D_00136980[];
extern char D_001369C0[];

int sceSifInitRpc(int x);
int sceSifInitIopHeap(void);
int sceSifAllocSysMemory(int a, int b, int c);
int LoaderSysPrintf(const char *fmt, ...);
int FlushCache(int x);
int sceSifSetDma(Block16 *args, int x);
int sceSifDmaStat(int handle);
int sceSifLoadModuleBuffer(int mem, int a, int b);
int sceSifFreeSysMemory(int mem);
int func_00128E6C(char *record, const char *module);
int func_001290C4(const char *s);
int func_001293B8(char *dst, const char *src, int len);

static inline int _loadIopModuleFromEEBuffer(int src, int size, int arg3, int arg4) {
    Block16 args;
    int size4;
    int mem;
    int handle;
    int ret;

    size4 = (size + 3) & -4;
    sceSifInitRpc(0);
    sceSifInitIopHeap();
    mem = sceSifAllocSysMemory(1, size4, 0);
    LoaderSysPrintf(D_00136900, mem, size4);
    FlushCache(0);
    args.w0 = src;
    args.w1 = mem;
    args.w2 = size4;
    args.w3 = 0;
    handle = sceSifSetDma(&args, 1);
    while (sceSifDmaStat(handle) >= 0)
        ;
    LoaderSysPrintf(D_00136948);
    ret = sceSifLoadModuleBuffer(mem, arg3, arg4);
    sceSifFreeSysMemory(mem);
    return ret;
}

static inline int setNewIopIdentifier(const char *module) {
    LoaderSysPrintf(D_00136980, module, D_0013A008);
    func_001293B8(D_0013CB90 + D_0013A008++ * 16, module, func_001290C4(module));
}

static inline int findIopIdentifier(const char *module) {
    int i;

    for (i = 0; i < D_0013A008; i++) {
        if (func_00128E6C(D_0013CB90 + i * 16, module) == 0)
            return i;
    }
    return -1;
}

int LoaderSysLoadIopModuleFromEEBuffer(const char *module, int src, int size, int arg3, int arg4) {
    int found;
    int ret;

    if (module != 0) {
        found = findIopIdentifier(module);
        if (found < 0) {
            ret = _loadIopModuleFromEEBuffer(src, size, arg3, arg4);
            if (ret >= 0)
                setNewIopIdentifier(module);
            return ret;
        }
        LoaderSysPrintf(D_001369C0, module, found);
        return 0;
    }
    return _loadIopModuleFromEEBuffer(src, size, arg3, arg4);
}
