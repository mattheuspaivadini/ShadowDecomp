/* KERNEL.XFF @ 0x01ABB0 (272 B) - isysRequestDeleteObj
 * Evidence: caller pc kept from $ra; an object delete callback (+0x18) is called once and cleared; then, under the inlined isysObjWaitSema/isysObjSignalSema pair, the word at +8 gets bit 0x10000, +4 = caller pc and the object is pushed on the pending-delete list at .bss+0x79188 (link +0x10). UNCONFIRMED: field names.
 */
struct IsysObj {
    char pad0[4];
    void *pc;
    unsigned int flags;
    char padC[4];
    struct IsysObj *next;
    char pad14[4];
    void (*delfn)(struct IsysObj *obj);
};
extern struct IsysObj *D_kernel_bss_79188;
extern int D_kernel_data_07CC;
extern int D_kernel_data_07D0;
extern int D_kernel_bss_7918C;
int GetThreadId(void);
int WaitSema(int sema);
int SignalSema(int sema);

static inline void isysObjWaitSema(void) {
    int tid = GetThreadId();

    if (tid == D_kernel_data_07CC) {
        D_kernel_data_07D0++;
    } else {
        WaitSema(D_kernel_bss_7918C);
        D_kernel_data_07CC = tid;
        D_kernel_data_07D0 = 1;
    }
}

static inline void isysObjSignalSema(void) {
    if (--D_kernel_data_07D0 == 0) {
        D_kernel_data_07CC = -1;
        SignalSema(D_kernel_bss_7918C);
    }
}


void isysRequestDeleteObj(struct IsysObj *obj) {
    register void *ra __asm__("$31");
    void *pc = ra;

    if (obj->delfn != 0) {
        obj->delfn(obj);
        obj->delfn = 0;
    }
    isysObjWaitSema();
    obj->flags |= 0x10000;
    obj->pc = pc;
    obj->next = D_kernel_bss_79188;
    D_kernel_bss_79188 = obj;
    isysObjSignalSema();
}
