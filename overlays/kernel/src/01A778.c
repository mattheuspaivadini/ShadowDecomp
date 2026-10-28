/* KERNEL.XFF @ 0x01A778 (332 B) - isysGroupForFirst
 * Evidence: inlined isysObjWaitSema/isysObjSignalSema around the group walk (head +0, next +0xE, entries at .bss+0x27100); returns the first entry whose lock byte (+0xC) is clear and whose object flag bit 0 (signed short +0xA) is clear, with that object's ref (byte +9) incremented. UNCONFIRMED: names.
 */
struct IsysObj {
    char pad[9];
    unsigned char ref;
    short flags;
};
struct GroupEnt {
    struct IsysObj *obj;
    char pad4[8];
    unsigned char lock;
    char padD;
    unsigned short next;
    char pad10[8];
};
struct IsysGroup {
    unsigned short first;
};
extern struct GroupEnt D_kernel_bss_27100[];
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

struct GroupEnt *isysGroupForFirst(struct IsysGroup *g) {
    struct GroupEnt *e;

    isysObjWaitSema();
    e = g->first ? &D_kernel_bss_27100[g->first] : 0;
    while (e != 0) {
        if (e->lock == 0 && !(e->obj->flags & 1)) {
            e->obj->ref++;
            break;
        }
        e = e->next ? &D_kernel_bss_27100[e->next] : 0;
    }
    isysObjSignalSema();
    return e;
}
