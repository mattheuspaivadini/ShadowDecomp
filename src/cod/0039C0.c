/* asm/cod/0039C0.s -> loaderLoop.
 * loader main loop: run the program, call the per-run callbacks (indexed for, reversed by loop.c), clean up, repeat. The end-of-image address is passed as (long): a DImode symbol load is not split into HIGH/LO_SUM, so its lui/addiu stay together (one dla).
 * MATCHED. */
extern int D_0013A010;          /* .sdata: heap start for the next program */
extern int D_0013A07C;          /* .sdata */
extern int loaderThreadId;
extern int ModuleStackStart;
extern void (*D_0013CFA0[10])(void);   /* per-run cleanup callbacks */
extern char D_16A398[];         /* end of the loader image (linker symbol) */
extern char D_00136CD0[];
extern char D_00136CE0[];
extern char D_00136CF0[];
extern char D_00136D00[];
extern char D_00136D10[];
extern char D_00136D60[];
extern char D_00136D78[];

register void *gp_reg asm ("$28");
register void *sp_reg asm ("$29");

void *malloc(unsigned int n);
void free(void *p);
void PutStringS(int color, const char *fmt, ...);
void *func_001283D0(void *dst, int c, unsigned int size);   /* memset */
void SetHeapStartPoint(int addr);
int  execProgWithThread(const char *name, int prio);
int  SleepThread(void);
void LoaderSysExecuteRecoveryFirstProcess(void);
int  ChangeThreadPriority(int thid, int prio);
void LoaderSysDeleteAllExternalIntcHandler(void);
void LoaderSysDeleteAllExternalThread(void);
void LoaderSysDeleteAllExternalSema(void);
void LoaderSysDeleteAllExternalIopMemory(void);
void ReinitDisp(void);

void loaderLoop(void) {
    void *p;
    int count;
    int i;

    count = 0;
    p = malloc(1);
    free(p);
    PutStringS(-0x100, D_00136CD0, gp_reg);
    PutStringS(-0x100, D_00136CE0, sp_reg);
    PutStringS(-0x100, D_00136CF0, p);
    PutStringS(-0x100, D_00136D00, (long)D_16A398);
    PutStringS(-0x100, D_00136D10, D_0013A010);
    func_001283D0(D_0013CFA0, 0, 0x28);
    D_0013A07C = 0;
    while (1) {
        SetHeapStartPoint(D_0013A010);
        ModuleStackStart = execProgWithThread(D_00136D60, 2);
        SleepThread();
        for (i = 0; i < 10; i++) {
            if (D_0013CFA0[i] != 0)
                D_0013CFA0[i]();
        }
        func_001283D0(D_0013CFA0, 0, 0x28);
        count++;
        D_0013A07C = 0;
        LoaderSysExecuteRecoveryFirstProcess();
        ChangeThreadPriority(loaderThreadId, 1);
        LoaderSysDeleteAllExternalIntcHandler();
        LoaderSysDeleteAllExternalThread();
        LoaderSysDeleteAllExternalSema();
        LoaderSysDeleteAllExternalIopMemory();
        ReinitDisp();
        PutStringS(-0x100, D_00136D78, count);
    }
}
