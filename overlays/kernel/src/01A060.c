/* KERNEL.XFF @ 0x01A060 (472 B) - _isysDeleteGroup
 * Evidence: under the inlined object lock, finds the object's group entry (list head +0xC, next +0x12) whose +4 equals the group; a missing entry is ignored when the third argument is set, otherwise reported with iosJumpRecoverPoint(.rodata+0x24F8); the entry is then marked and pushed on the release list at .bss+0x79184. The found path is a goto into the release code. UNCONFIRMED: names.
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

void _isysDeleteGroup(struct IsysObjHdr *obj, void *group, int quiet) {
    struct GroupEnt *e;

    isysObjWaitSema();
    e = obj->groups ? &D_kernel_bss_27100[obj->groups] : 0;
    while (e != 0) {
        if (e->unk4 == (int)group) {
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
