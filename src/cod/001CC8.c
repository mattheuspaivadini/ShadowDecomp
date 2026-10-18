/* asm/cod/001CC8.s -> _execProgWithThread.
 * _execProgWithThread; version-id address built by an asm volatile (lui; nop; addiu; nop) like the original, PutStringS third argument pinned in a register, thread entry loaded first (Session 23)
 * MATCHED. */
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
    int vid;

    t = GetThreadId(a0);
    r = func_00100D48(a0);
    if (r != 0) {
        fn = *(int *)(r + 0x10);
        D_00131C44[0] = r;
        HeapStart = D_00139E04;
        __asm__ volatile ("lui %0, %%hi(__loader_version_id__)
	nop
	addiu %0, %0, %%lo(__loader_version_id__)
	nop" : "=r" (vid));
        FlushCache(0);
        FlushCache(2);
        LoaderSysPrintf((int)D_001363D0, fn, vid);
        ((int (*)(int, int))fn)(1, vid);
    } else {
        __asm__ ("" : "+r" (r));
        PutStringS(0xFF804000, (int)D_00136508, r);
    }
    LoaderSysDeleteExternalThreadList(t);
    return ExitDeleteThread();
}
