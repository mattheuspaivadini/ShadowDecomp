/* KERNEL.XFF @ 0x02F578 (116 B) - Sg2ExPcmOutputBufferClear
 * Evidence: -1 while the output buffer pointer (.bss+0x9BE2C) is set; otherwise the static .text+0x2E460 (out, size +0x10) under DIntr/EIntr, the static .text+0x2E568 (out, size), position (+0x18) = 0, returns 0. UNCONFIRMED: names.
 */
struct PcmOutput {
    int unk0;
    int unk4;
    int unk8;
    void *buf;
    int size;
    int unk14;
    int pos;
};
extern struct PcmOutput D_kernel_bss_9BE20;
int DIntr(void);
int EIntr(void);
void func_02E460(struct PcmOutput *o, int size);
void func_02E568(struct PcmOutput *o, int size);

int Sg2ExPcmOutputBufferClear(void) {
    struct PcmOutput *o = &D_kernel_bss_9BE20;
    int intr;

    if (o->buf != 0) {
        return -1;
    }
    intr = DIntr();
    func_02E460(o, o->size);
    if (intr) {
        EIntr();
    }
    func_02E568(o, o->size);
    o->pos = 0;
    return 0;
}
