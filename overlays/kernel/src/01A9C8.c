/* KERNEL.XFF @ 0x01A9C8 (296 B) - isysGroupGetObjNumForce
 * Evidence: inlined isysObjWaitSema/isysObjSignalSema around a walk of the group list (head index +0, next index +0xE in the 0x18-byte entries at .bss+0x27100) counting every entry. UNCONFIRMED: names.
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
    char pad4[0xA];
    unsigned short next;
    char pad10[8];
};
struct IsysGroup {
    unsigned short first;
};
extern struct GroupEnt D_kernel_bss_27100[];

int isysGroupGetObjNumForce(struct IsysGroup *g) {
    struct GroupEnt *e;
    int n;

    isysObjWaitSema();
    e = g->first ? &D_kernel_bss_27100[g->first] : 0;
    for (n = 0; e != 0; n++) {
        e = e->next ? &D_kernel_bss_27100[e->next] : 0;
    }
    isysObjSignalSema();
    return n;
}
