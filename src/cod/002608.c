/* asm/cod/002608.s -> lower_external_threads.
 * loader recovery: inline helpers for the thread/heap list sweeps (Session 19)
 * MATCHED. */
extern int D_0013B790[256];  /* external thread list, -1 = free */
extern int D_0013C790[256];  /* external IOP heap list, 0 = free */

int  GetThreadId(void);
int  ChangeThreadPriority(int thid, int prio);
void LoaderSysDeleteAllExternalIntcHandler(void);
int  TerminateThread(int thid);
int  DeleteThread(int thid);
void LoaderSysDeleteAllExternalSema(void);
void LoaderSysFlushPrint(void);
void sceSifInitRpc(int mode);
int  sceSifInitIopHeap(void);
int  sceSifFreeIopHeap(void *addr);

static inline void lower_external_threads(void) {
    int me = GetThreadId();
    int i;

    for (i = 0; i < 256; i++) {
        if (D_0013B790[i] != me && D_0013B790[i] >= 0)
            ChangeThreadPriority(D_0013B790[i], 0x7F);
    }
}

static inline void delete_external_threads(void) {
    int me = GetThreadId();
    int i;

    for (i = 0; i < 256; i++) {
        if (D_0013B790[i] != me && D_0013B790[i] >= 0) {
            TerminateThread(D_0013B790[i]);
            DeleteThread(D_0013B790[i]);
            D_0013B790[i] = -1;
        }
    }
}

static inline void free_external_iop_heap(void) {
    int i;

    for (i = 0; i < 256; i++) {
        if (D_0013C790[i] != 0) {
            sceSifFreeIopHeap((void *)D_0013C790[i]);
            D_0013C790[i] = 0;
        }
    }
}

void LoaderSysExecuteRecoveryFirstProcess(void) {
    ChangeThreadPriority(GetThreadId(), 1);
    LoaderSysDeleteAllExternalIntcHandler();
    lower_external_threads();
    delete_external_threads();
    LoaderSysDeleteAllExternalSema();
    LoaderSysFlushPrint();
    sceSifInitRpc(0);
    sceSifInitIopHeap();
    free_external_iop_heap();
}
