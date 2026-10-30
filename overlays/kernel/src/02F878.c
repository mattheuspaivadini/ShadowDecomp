/* KERNEL.XFF @ 0x02f878 (188 B) - Sg2ExPcmTickProc
 * Evidence: after the sibling tick (func_02EAA8) the record at .bss+0x9BE20 is
 * skipped when bit 1 of +4 is set.  Otherwise the IOP transfer offset
 * (Sg2StPcmIopTransOffset, /2 via the sra-halving idiom) is divided by the
 * record's +0x1A8/2; when the quotient differs from the +0x1B0 counter the
 * record is re-sent (func_02E460 and func_02E568, both with the halved count)
 * and the counter advances modulo 2 (`x - (x/2)*2`).
 * Evaluation order matters: the transfer-offset call must be written *before*
 * the +0x1A8 load, or the load is hoisted above the call.
 * UNCONFIRMED: record field names and the callee prototypes.
 * Flags: -g0 (delayed-branch scheduler) required.
 */
struct PcmOutput {
    int f0;
    int f4;
    int f8;
    void *buf;
    int f10;
    int f14;
    int f18;
    char pad1C[0x1A4 - 0x1C];
    int f1A4;
    int f1A8;
    int f1AC;
    int f1B0;
};
extern struct PcmOutput D_kernel_bss_9BE20;
void func_02EAA8(void);
int Sg2StPcmIopTransOffset(void);
void func_02E460(struct PcmOutput *p, int n);
void func_02E568(struct PcmOutput *p, int n);

void Sg2ExPcmTickProc(void) {
    int n;
    int v;

    func_02EAA8();
    if (D_kernel_bss_9BE20.f4 & 2) {
        return;
    }
    v = Sg2StPcmIopTransOffset() / 2;
    n = D_kernel_bss_9BE20.f1A8 / 2;
    if (v / n != D_kernel_bss_9BE20.f1B0) {
        func_02E460(&D_kernel_bss_9BE20, n);
        func_02E568(&D_kernel_bss_9BE20, n);
        D_kernel_bss_9BE20.f1B0 = (D_kernel_bss_9BE20.f1B0 + 1) % 2;
    }
}
