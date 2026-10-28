/* KERNEL.XFF @ 0x02E460 (264 B) - func_02E460 (static, no symbol in the shipped .symtab)
 * Evidence: PCM output tick: skipped while status (+4) bit 2 is set; clears the mix buffer (func_02DD58), and for each active input (bit 0 of the four 0x1D4-byte records at .bss+0x9BFD8) the statics at .text+0x2E2B8 (input, n) and func_02E280 (mix, input voice +4, n); then .text+0x2E178, .text+0x2E118 when mode (+0) is 0, and .text+0x2DD78 as a tail call. UNCONFIRMED: names; Ghidra FUN_0022e460.
 */
struct PcmMix {
    int num;
    int *tbl;
};
struct PcmInputVoice {
    int unk0;
};
struct PcmInput {
    unsigned int status;
    struct PcmInputVoice v;
    char pad8[0x1D4 - 8];
};
struct PcmOutput {
    int mode;
    unsigned int status;
    struct PcmMix mix;
};
extern struct PcmInput D_kernel_bss_9BFD8[4];
void func_02DD58(struct PcmMix *m, int n);
void func_02E2B8(struct PcmInput *in, int n);
void func_02E280(struct PcmMix *m, struct PcmInputVoice *v, int n);
void func_02E178(struct PcmMix *m, int n);
void func_02E118(struct PcmMix *m, int n);
void func_02DD78(struct PcmMix *m, int n);

void func_02E460(struct PcmOutput *o, int n) {
    int i;

    if (o->status & 4) {
        return;
    }
    func_02DD58(&o->mix, n);
    for (i = 0; i < 4; i++) {
        if (D_kernel_bss_9BFD8[i].status & 1) {
            func_02E2B8(&D_kernel_bss_9BFD8[i], n);
            func_02E280(&o->mix, &D_kernel_bss_9BFD8[i].v, n);
        }
    }
    func_02E178(&o->mix, n);
    if (o->mode == 0) {
        func_02E118(&o->mix, n);
    }
    func_02DD78(&o->mix, n);
}
