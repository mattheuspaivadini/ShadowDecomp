/* KERNEL.XFF @ 0x019BB8 (608 B) - isysAddGroupWithLinkParam
 * Evidence: under the inlined object lock, pops an entry from the free list at .bss+0x79180 (next index +0xE), fills obj/group/param (+0, +4, +8; iosJumpRecoverPoint(.rodata+0x24C8, group, obj) when either is NULL), inserts it after the group's tail with the static at .text+0x197E8 (mode 1) and appends it to the object's group list (head +0xC, tail +0xE, links +0x12/+0x14); returns entry != NULL. The NULL tests after the dereferences survive: built with -fno-delete-null-pointer-checks. UNCONFIRMED: names.
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

int isysAddGroupWithLinkParam(struct IsysObjHdr *obj, struct IsysGroup *group, int unused, int param) {
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
    func_0197E8(getEnt(e->group->last), e, 1);
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
