/* KERNEL.XFF @ 0x02EEB8 (112 B) - Sg2ExPcmInputOpen   [MATCH: -G0]
 * Evidence: opens an ExPcm input: tail-calls func_02ED28(a0, p->f10/2,
 * D_bss_9BE30/2, p->f0C, mode, p->f14, p->f18, p->f10) with args 5-8 in
 * $t0..$t3.  The two signed halvings are the classic srl31/addu/sra sequence;
 * mode is 4 unless both p->f14 and p->f18 are zero, in which case it is 2
 * (bnez/bnez tree with `li t0,2` in the beqz delay slot and an aligned `nop`
 * before the f14 arm).  The pointer argument is copied to $t4 and every field
 * read goes through it; $t3 and $t1 hold copies of p->f10 and p->f14.
 * UNCONFIRMED: struct/field names, prototypes.
 * Lever: naming the four argument subexpressions as locals declared in the order
 * half, rate, mode, out reproduces the image's evaluation order (divisions and
 * the mode branch first, p->f0C loaded last into $a3); the second pointer pin
 * `register struct PcmArg *p asm("$12")` is required for $t4.
 */
struct PcmArg {
    int f00;
    int f04;
    int f08;
    int f0C;
    int f10;
    int f14;
    int f18;
};
extern int D_kernel_bss_9BE30;
extern int func_02ED28(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7);

int Sg2ExPcmInputOpen(int a0, struct PcmArg *arg) {
    register struct PcmArg *p asm("$12") = arg;
    int half = p->f10 / 2;
    int rate = D_kernel_bss_9BE30 / 2;
    int mode = (p->f14 || p->f18) ? 4 : 2;
    int out = p->f0C;

    return func_02ED28(a0, half, rate, out, mode, p->f14, p->f18, p->f10);
}
