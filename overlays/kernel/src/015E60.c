/* KERNEL.XFF @ 0x015E60 (92 B) - iosResetPath   [MATCH: -G0]
 * Evidence: `lui/ori 0x1000_3C10` + store 1, then the VU0 status bit
 * (cfc2.ni/ori 0x200/ctc2.ni/sync.p on $vi28), then the two 16-byte quads at
 * .data+0x5C0/+0x5D0 are copied to 0x1000_5000 with lq/sq, and finally 1 is
 * stored to 0x1000_3000.  The image materialises the constant 1 TWICE
 * (`addiu a0,zero,1` for 0x10003C10, `addiu a3,zero,1` for 0x10003000) because
 * a0 is reused for the .data pointer in between.
 * Lever: the first store's value is a *register variable pinned to $4*
 * (`register int one asm("$4") = 1;`).  Its live range ends at that store, so
 * the .data pointer legitimately takes a0 next, and the constant is dead by the
 * time the last store needs it -> gcc re-materialises `addiu a3,zero,1` and
 * emits `sw`.  Any plain SImode `1` lets cse keep one register (88 B), and a
 * DImode `1` (which keeps both materialisations) stores with `sd` (92 B, 1/23).
 * UNCONFIRMED: prototypes; the type/name of the .data+0x5C0 quad pair
 * (`D_kernel_data_05C0`, reused from the s70 draft); the `*(&...[0] + 0)`
 * no-op that keeps the lq/sq pair adjacent is a shape artefact.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
extern u_long128 D_kernel_data_05C0[2];

void iosResetPath(void) {
    register int stat __asm__("$3") = 0;

    {
        register int one asm("$4") = 1;

        *(volatile int *)0x10003C10 = one;
    }
    __asm__ __volatile__(
        "cfc2.ni %0, $vi28\n"
        "ori %0, %0, 0x200\n"
        "ctc2.ni %0, $vi28\n"
        "sync.p\n" : "+r"(stat));
    *(&D_kernel_data_05C0[0] + 0);
    *(volatile u_long128 *)0x10005000 = D_kernel_data_05C0[0];
    *(volatile u_long128 *)0x10005000 = D_kernel_data_05C0[1];
    *(volatile int *)0x10003000 = 1;
}
