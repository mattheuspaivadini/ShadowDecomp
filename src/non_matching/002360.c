/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 29 [cc=296].
 * R2 w45a_0: reg-alloc ($gp reload pair after the first call)
 * The original .s stays in the build (asm/cod/002360.s); this C
 * draft (Session 8) is kept for the record. */
extern char D_001368A0[];
extern char D_001368E0[];
extern int  eeRegInfo[];

int  GetThreadId(int a0);
void LoaderSysExecuteRecoveryFirstProcess(void);
void ChangeThreadPriority(int a0, int a1);
void EIntr(void);
void LoaderSysPrintf(int a0, int a1);
int  iGetCop0(int a0);
void LoaderSysJumpRecoverPointNoStateSetting(int a0, ...);

void func_00102360(int a0, int a1, int a2, int a3, int a4, int *a5) {
    int *q;
    int *p;
    int t;
    int i;

    t = GetThreadId(a0);
    LoaderSysExecuteRecoveryFirstProcess();
    ChangeThreadPriority(t, 0x7F);
    EIntr();
    LoaderSysPrintf((int)D_001368A0, t);
    q = a5;
    p = eeRegInfo;
    for (i = 0; i < 0x20; i++) {
        p[0] = q[0];
        q += 4;
        p[0x40] = iGetCop0(i);
        p += 2;
    }
    *(int *)((char *)eeRegInfo + 0x170) = a2;
    *(int *)((char *)eeRegInfo + 0x168) = a1;
    LoaderSysJumpRecoverPointNoStateSetting((int)D_001368E0);
}
