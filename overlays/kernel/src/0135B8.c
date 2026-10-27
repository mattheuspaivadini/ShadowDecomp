/* KERNEL.XFF @ 0x0135B8 (264 B) - iosDlSwap
 * Evidence: under the DL semaphore (.bss+0x1EAD0, volatile: lui/addiu+0 load), toggles workBufId; under the isys object lock walks the new buffer's group (+0x20 + id*4) with isysGroupForFirstForce/NextForce, unlocking each object (isysObjDeleteUnLock) and decrementing lockNum[id] (+0x28); exits the group from the last object, isysDeleteGroupAllObj(group), releases the object lock, calls static .text+0x12BF8, and sibling SignalSema. DL work block at .bss+0x1EAD8 (volatile struct). UNCONFIRMED: names, group-walk prototypes.
 */
struct DLWork {
    char *base[2];
    char *buf[2];
    char *packet;
    int layerNum;
    int workBufId;
    int layer;
    char group[2][4];
    int lockNum[2];
};
struct GroupEnt {
    void *obj;
};
extern volatile struct DLWork D_kernel_bss_1EAD8;
extern volatile int D_kernel_bss_1EAD0;
int WaitSema(int sema);
int SignalSema(int sema);
void isysObjWaitSema(void);
void isysObjSignalSema(void);
struct GroupEnt *isysGroupForFirstForce(void *group, int arg);
struct GroupEnt *isysGroupForNextForce(struct GroupEnt *g, int arg);
void isysGroupForExit(void *obj, int arg);
void isysObjDeleteUnLock(void *obj);
void isysDeleteGroupAllObj(void *group);
static void func_012BF8(void);

void iosDlSwap(void) {
    struct GroupEnt *g;
    void *obj = 0;
    int id;
    void *group;

    WaitSema(D_kernel_bss_1EAD0);
    D_kernel_bss_1EAD8.workBufId ^= 1;
    id = D_kernel_bss_1EAD8.workBufId;
    group = (void *)D_kernel_bss_1EAD8.group[id];
    isysObjWaitSema();
    for (g = isysGroupForFirstForce(group, 0); g != 0; g = isysGroupForNextForce(g, 0)) {
        obj = g->obj;
        isysObjDeleteUnLock(obj);
        D_kernel_bss_1EAD8.lockNum[id]--;
    }
    if (obj) {
        isysGroupForExit(obj, 0);
    }
    isysDeleteGroupAllObj(group);
    isysObjSignalSema();
    func_012BF8();
    SignalSema(D_kernel_bss_1EAD0);
}
