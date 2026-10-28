/* KERNEL.XFF @ 0x01A420 (404 B) - isysDeleteGroupAllObj
 * Evidence: under the inlined object lock, every entry of the group list (head +0, next +0xE, 0x18-byte entries at .bss+0x27100) not yet marked (+0xC != 1) is marked, linked (+0x16 = index of the previous head) onto the release list at .bss+0x79184, and its +4 word is cleared; the group head/tail (+2, +0) are reset. UNCONFIRMED: names.
 */
struct GroupEnt {
    void *obj;
    int unk4;
    char pad8[4];
    unsigned char lock;
    char padD;
    unsigned short next;
    char pad10[6];
    unsigned short link;
};
struct IsysGroup {
    unsigned short first;
    unsigned short last;
};
extern struct GroupEnt D_kernel_bss_27100[];
extern struct GroupEnt *D_kernel_bss_79184;
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


void isysDeleteGroupAllObj(struct IsysGroup *g) {
    struct GroupEnt *e;

    isysObjWaitSema();
    e = g->first ? &D_kernel_bss_27100[g->first] : 0;
    while (e != 0) {
        if (e->lock != 1) {
            e->lock = 1;
            e->link = D_kernel_bss_79184 ? D_kernel_bss_79184 - D_kernel_bss_27100 : 0;
            D_kernel_bss_79184 = e;
        }
        e->unk4 = 0;
        e = e->next ? &D_kernel_bss_27100[e->next] : 0;
    }
    g->last = 0;
    g->first = 0;
    isysObjSignalSema();
}
