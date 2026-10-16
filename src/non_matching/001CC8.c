/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 12 [cc=296].
 * R2 w45a_0: dead 0xFF804000 as func_00105990's $a0
 * The original .s stays in the build (asm/cod/001CC8.s); this C
 * draft (Session 8) is kept for the record. */
extern int  HeapStart;     /* .sdata, right below D_00139E04 */
extern int  D_00139E04;
extern int  D_00131C44[];   /* .data slot, absolute address */
extern char __loader_version_id__[];
extern char D_001363D0[];
extern char D_00136508[];

int  GetThreadId(int a0);
int  func_00100D48(int a0);
void FlushCache(int a0);
void LoaderSysPrintf(int a0, int a1, int a2);
void PutStringS(int a0, int a1, int a2);
int  LoaderSysDeleteExternalThreadList(int a0);
int  ExitDeleteThread(void);

int _execProgWithThread(int a0) {
    int t;
    int r;
    int fn;

    t = GetThreadId(a0);
    r = func_00100D48(a0);
    if (r != 0) {
        D_00131C44[0] = r;
        HeapStart = D_00139E04;
        fn = *(int *)(r + 0x10);
        FlushCache(0);
        FlushCache(2);
        LoaderSysPrintf((int)D_001363D0, fn, (int)__loader_version_id__);
        ((int (*)(int, int))fn)(1, (int)__loader_version_id__);
    } else {
        PutStringS(0xFF804000, (int)D_00136508, r);
    }
    LoaderSysDeleteExternalThreadList(t);
    return ExitDeleteThread();
}
