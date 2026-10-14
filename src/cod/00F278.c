/* asm/cod/00F278.s -> func_0010F278 @ 0x0010F278 (0x60 bytes, 24 insns)
 *
 * Register the same DMA-completion handler func_0010F7C0 on DMA channels 1, 2
 * and 3 (func_00106C90 is the `addiu $v1,$zero,0xD; syscall 0` wrapper =
 * AddDmacHandler(channel, handler)) and publish a0 in D_00132668:
 *   D_00132668[0] = a0;
 *   func_00106C90(1, func_0010F7C0);
 *   func_00106C90(2, func_0010F7C0);
 *   func_00106C90(3, func_0010F7C0);
 *   return a0;
 * D_00132668 is addressed absolutely (lui/%lo), the handler address is built
 * once into $s0, and a0 is kept in $s1 across the three calls. The saves are 16
 * bytes apart ($s0 at 0x00, $s1 at 0x10, $ra at 0x20) - the cc=29 slot layout.
 * MATCH GUESS: cc=29 */
extern int D_00132668[];   /* .data 0x00132668: lui/%lo (non-small) */
extern void func_0010F7C0(void);
extern int func_00106C90(int a0, void (*a1)(void));

int func_0010F278(int a0) {
    D_00132668[0] = a0;
    func_00106C90(1, func_0010F7C0);
    func_00106C90(2, func_0010F7C0);
    func_00106C90(3, func_0010F7C0);
    return a0;
}
