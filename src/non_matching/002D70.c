/* STATUS (Session 6, step 2): -O2/-O3 discriminating experiment.
 * Plain static helpers (no `inline` keyword). At -O2 ee-gcc emits out-of-line
 * copies + `jal`; at -O3 (-finline-functions) both helpers are integrated and
 * no out-of-line copy remains - the shape the original image shows (there is
 * no out-of-line `_loadIopModuleFromEEBuffer` anywhere in the image).
 * See docs/compiler.md section 2.3.
 *
 * asm/cod/002D70.s -> LoaderSysLoadIopModuleFromEEBuffer @ 0x00102D70
 * (0x26C bytes): search the 16-byte records at D_0013CB90 for `module`
 * (func_00128E6C == 0 means found), print the "exists" diagnostic and return 0
 * when present; otherwise load the IOP module from the EE buffer through two
 * inlined static helpers (the load sequence appears TWICE - once for the
 * module != 0 path with registration, once for module == 0 without).
 */
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

static int _loadIopModuleFromEEBuffer(int src, int size, int arg3, int arg4) {
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
    sceSifLoadModuleBuffer(mem, arg3, arg4);
    ret = sceSifFreeSysMemory(mem);
    return ret;
}

static int setNewIopIdentifier(const char *module) {
    LoaderSysPrintf(D_00136980, module, D_0013A008);
    func_001293B8(D_0013CB90 + D_0013A008 * 16, module,
                  func_001290C4(module));
    D_0013A008 = D_0013A008 + 1;
}

int LoaderSysLoadIopModuleFromEEBuffer(const char *module, int src, int size,
                                       int arg3, int arg4) {
    int index;
    int ret;

    if (module != 0) {
        for (index = 0; index < D_0013A008; index++) {
            if (func_00128E6C(D_0013CB90 + index * 16, module) == 0)
                break;
        }
        if (index < D_0013A008) {
            LoaderSysPrintf(D_001369C0, module, index);
            return 0;
        }
        ret = _loadIopModuleFromEEBuffer(src, size, arg3, arg4);
        if (ret < 0)
            return ret;
        setNewIopIdentifier(module);
        return ret;
    }
    return _loadIopModuleFromEEBuffer(src, size, arg3, arg4);
}
