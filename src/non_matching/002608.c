/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 21 [cc=296].
 * R2 w45a_1: rotated-loop (three 256-entry sweeps, swapped roles)
 * The original .s stays in the build (asm/cod/002608.s); this C
 * draft (Session 8) is kept for the record. */
extern int D_0013B790[];    /* lui/%lo */
extern int D_0013C790[];    /* lui/%lo */

int  GetThreadId(void);
int  ChangeThreadPriority(int a0, int a1);
int  LoaderSysDeleteAllExternalIntcHandler(void);
int  TerminateThread(void);
int  DeleteThread(int a0);
int  LoaderSysDeleteAllExternalSema(void);
int  LoaderSysFlushPrint(void);
int  sceSifInitRpc(int a0);
int  sceSifInitIopHeap(void);
int  sceSifFreeIopHeap(int a0);

void LoaderSysExecuteRecoveryFirstProcess(void) {
    int i;
    int v;
    int t;
    int *p;

    i = 0xFF;
    ChangeThreadPriority(GetThreadId(), 1);
    LoaderSysDeleteAllExternalIntcHandler();
    t = GetThreadId();
    p = D_0013B790;
    v = *p;
    while (i >= 0) {
        if (v != t && v >= 0)
            ChangeThreadPriority(v, 0x7F);
        i--;
        p++;
        v = *p;
    }
    {
        int j;
        int n;
        int *q;

        t = GetThreadId();
        n = -1;
        q = D_0013B790;
        for (j = 0xFF; j >= 0; j--) {
            if (*q != t && *q >= 0) {
                TerminateThread();
                DeleteThread(*q);
                *q = n;
            }
            q++;
        }
    }
    LoaderSysDeleteAllExternalSema();
    LoaderSysFlushPrint();
    sceSifInitRpc(0);
    sceSifInitIopHeap();
    {
        int j;
        int *q;

        q = D_0013C790;
        for (j = 0xFF; j >= 0; j--) {
            if (*q != 0) {
                sceSifFreeIopHeap(*q);
                *q = 0;
            }
            q++;
        }
    }
}
