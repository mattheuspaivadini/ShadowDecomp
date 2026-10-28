/* KERNEL.XFF @ 0x01A8C8 (252 B) - isysGroupForFirstForce
 * Evidence: inlined isysObjWaitSema/isysObjSignalSema around the group head lookup (entry index +0 into the 0x18-byte entry table at .bss+0x27100, 0 = none); the first entry's object gets ref++ (byte +9) without the lock/flag checks of isysGroupForFirst. UNCONFIRMED: names.
 */
struct IsysObj {
    char pad[9];
    unsigned char ref;
};
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

struct GroupEnt {
    struct IsysObj *obj;
    char pad4[0x14];
};
struct IsysGroup {
    unsigned short first;
};
extern struct GroupEnt D_kernel_bss_27100[];

struct GroupEnt *isysGroupForFirstForce(struct IsysGroup *g) {
    struct GroupEnt *e;

    isysObjWaitSema();
    e = g->first ? &D_kernel_bss_27100[g->first] : 0;
    if (e != 0) {
        e->obj->ref++;
    }
    isysObjSignalSema();
    return e;
}
