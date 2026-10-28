/* KERNEL.XFF @ 0x01A238 (488 B) - isysDeleteGroupWithLinkParam
 * Evidence: same as _isysDeleteGroup (inlined lock, release list .bss+0x79184, assert .rodata+0x24F8) but an entry only matches when its +4 equals the group and its +8 word is non-zero; the third argument is unused and the fourth is the quiet flag. UNCONFIRMED: names.
 */
struct GroupEnt {
    void *obj;
    int unk4;
    void *group;
    unsigned char lock;
    char padD;
    unsigned short next;
    char pad10[2];
    unsigned short onext;
    char pad14[2];
    unsigned short link;
};
struct IsysObjHdr {
    char pad0[0xC];
    unsigned short groups;
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


extern char D_kernel_rodata_24F8[];
void iosJumpRecoverPoint(const char *fmt, ...);

void isysDeleteGroupWithLinkParam(struct IsysObjHdr *obj, void *group, int unused, int quiet) {
    struct GroupEnt *e;

    isysObjWaitSema();
    e = obj->groups ? &D_kernel_bss_27100[obj->groups] : 0;
    while (e != 0) {
        if (e->unk4 == (int)group && e->group != 0) {
            goto found;
        }
        e = e->onext ? &D_kernel_bss_27100[e->onext] : 0;
    }
    if (quiet) {
        goto out;
    }
    iosJumpRecoverPoint(D_kernel_rodata_24F8);
found:
    if (e->lock != 1) {
        e->lock = 1;
        e->link = D_kernel_bss_79184 ? D_kernel_bss_79184 - D_kernel_bss_27100 : 0;
        D_kernel_bss_79184 = e;
    }
out:
    isysObjSignalSema();
}
