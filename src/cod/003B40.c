/* asm/cod/003B40.s -> start.
 * loader entry: argv echo, program name copy, loader init, heap start from two linker symbols (asm volatile lui;nop;addiu;nop), $sp saved, loaderLoop; __main called explicitly since the image names it start (Session 33).
 * MATCHED. */
extern int loaderThreadId;
extern int D_0013A010;          /* .sdata: heap start for the next program */
extern void *spReg;
extern char D_0013CF90[16];     /* program name */
extern char D_16A398[];         /* end of the loader image (linker symbol) */
extern char D_40000[];          /* linker symbol */
extern char D_00136D88[];
extern char D_00136DA0[];
extern char D_00136DB8[];

register void *sp_reg asm ("$29");

#define LA(var, sym) __asm__ volatile ("lui %0, %%hi(" #sym ")\n\tnop\n\taddiu %0, %0, %%lo(" #sym ")\n\tnop" : "=r" (var))

int func_001285C0(const char *fmt, ...);   /* printf */
char *func_001293B8(char *dst, const char *src, int len);   /* strncpy */
int GetThreadId(void);
void InitDisp(void);
void initmemprintf(int start, int end);
void func_001033B0(void);
void InitException(void);
void LoaderSysInitExternalIntcHandlerList(void);
void LoaderSysInitExternalThreadList(void);
void LoaderSysInitExternalSemaList(void);
void LoaderSysInitExternalIopMemoryList(void);
int ChangeThreadPriority(int thid, int prio);
void PutStringS(int color, const char *fmt, ...);
void loaderLoop(void);
void __main(void);

int start(int argc, char **argv) {
    int i;
    int end, size;

    __main();

    func_001285C0(D_00136D88, argc);
    for (i = 0; i < argc; i++)
        func_001285C0(D_00136DA0, i, argv[i]);
    if (argc != 0) {
        func_001293B8(D_0013CF90, argv[0], 0x10);
        D_0013CF90[15] = 0;
    } else {
        D_0013CF90[0] = 0;
    }
    loaderThreadId = GetThreadId();
    InitDisp();
    initmemprintf(0x2000000, 0x7FFFF00);
    func_001033B0();
    LA(end, D_16A398);
    LA(size, D_40000);
    D_0013A010 = (end + size + 15) & ~15;
    InitException();
    LoaderSysInitExternalIntcHandlerList();
    LoaderSysInitExternalThreadList();
    LoaderSysInitExternalSemaList();
    LoaderSysInitExternalIopMemoryList();
    ChangeThreadPriority(loaderThreadId, 1);
    PutStringS(-0x100, D_00136DB8);
    spReg = sp_reg;
    loaderLoop();
    return 0;
}
