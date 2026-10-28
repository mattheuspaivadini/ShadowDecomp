/* KERNEL.XFF @ 0x01E078 (368 B) - sndSepReq
 * Evidence: under the SEP semaphore (.bss+0x7D1D0) takes the first free 0x70-byte SEP slot of 32 (.bss+0x7C3D0, used word +0); stores the four request words (+0x34/+0x38/+0x40/+0x44), the VAB reference (+0x10), clears bit 32 of the 64-bit flags at +8, sets the 3-bit type at bit 34 and bit 37, clears +0x3C, calls the optional init callback(slot), then records soundTickProcCnt at +0x60 and marks the slot used. Returns the slot or NULL. UNCONFIRMED: names.
 */
struct SepSlot {
    int used;
    int unk4;
    unsigned long lo : 32;
    unsigned long paused : 1;
    unsigned long f33 : 1;
    unsigned long type : 3;
    unsigned long active : 1;
    unsigned long rest : 26;
    void *vab;
    char pad14[0x20];
    int a;
    int b;
    int unk3C;
    int c;
    int d;
    char pad48[0x18];
    int tick;
    char pad64[0xC];
};
extern struct SepSlot D_kernel_bss_7C3D0[32];
extern int D_kernel_bss_7D1D0;
extern int soundTickProcCnt;
int WaitSema(int sema);
int SignalSema(int sema);

struct SepSlot *sndSepReq(int a, int b, int c, int d, void (*cb)(struct SepSlot *s), int type, void *vab) {
    struct SepSlot *s = 0;
    int i;

    WaitSema(D_kernel_bss_7D1D0);
    for (i = 0; i < 32; i++) {
        if (D_kernel_bss_7C3D0[i].used == 0) {
            goto found;
        }
    }
    goto out;
found:
    s = &D_kernel_bss_7C3D0[i];
    s->a = a;
    s->b = b;
    s->c = c;
    s->d = d;
    s->vab = vab;
    s->paused = 0;
    s->type = type;
    s->active = 1;
    s->unk3C = 0;
    if (cb != 0) {
        cb(s);
    }
    s->tick = soundTickProcCnt;
    s->used = 1;
out:
    SignalSema(D_kernel_bss_7D1D0);
    return s;
}
