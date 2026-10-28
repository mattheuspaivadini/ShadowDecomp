/* KERNEL.XFF @ 0x019E18 (584 B) - isysAddGroupRelativeWithLinkParam
 * Evidence: isysAddGroupWithLinkParam with an explicit insertion point: the static at .text+0x197E8 gets (rel, entry, mode) from the third and fourth arguments; fifth unused, sixth = link param. Same -fno-delete-null-pointer-checks requirement. UNCONFIRMED: names.
 */
struct IsysGroup {
    unsigned short first;
    unsigned short last;
};
struct IsysObjHdr {
    char pad0[0xC];
    unsigned short ghead;
    unsigned short gtail;
};
struct GroupEnt {
    struct IsysObjHdr *obj;
    struct IsysGroup *group;
    int param;
    unsigned char lock;
    char padD;
    unsigned short next;
    unsigned short prev;
    unsigned short onext;
    unsigned short oprev;
    unsigned short link;
};
extern struct GroupEnt D_kernel_bss_27100[];
extern struct GroupEnt *D_kernel_bss_79180;
extern char D_kernel_rodata_24C8[];
void iosJumpRecoverPoint(const char *fmt, ...);
void func_0197E8(struct GroupEnt *after, struct GroupEnt *e, int a);

#define getEnt(i) ((i) ? &D_kernel_bss_27100[i] : 0)

#define getIdx(e) ((e) ? (e) - D_kernel_bss_27100 : 0)

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

int isysAddGroupRelativeWithLinkParam(struct IsysObjHdr *obj, struct IsysGroup *group, struct GroupEnt *rel, int mode, int unused, int param) {
    struct GroupEnt *e;
    struct GroupEnt **fl;

    isysObjWaitSema();
    fl = &D_kernel_bss_79180;
    e = *fl;
    if (e != 0) {
        *fl = getEnt(e->next);
    }
    e->param = param;
    e->obj = obj;
    e->group = group;
    if (group == 0 || obj == 0) {
        iosJumpRecoverPoint(D_kernel_rodata_24C8, group, obj);
    }
    func_0197E8(rel, e, mode);
    if (obj->ghead == 0) {
        e->oprev = 0;
        obj->ghead = getIdx(e);
    } else {
        e->oprev = obj->gtail;
        getEnt(obj->gtail)->onext = getIdx(e);
    }
    e->onext = 0;
    obj->gtail = getIdx(e);
    isysObjSignalSema();
    return e != 0;
}
