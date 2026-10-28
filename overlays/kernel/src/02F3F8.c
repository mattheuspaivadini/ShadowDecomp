/* KERNEL.XFF @ 0x02f3f8 (60 B) - Sg2ExPcmInputAutoFilterCtrl
 * Evidence: `sltiu a0,4` guards the store; the address is built as
 *   idx*196 + ch*468 + .bss+0x9BFD0
 * (196 = ((idx*3)<<4 + idx)<<2, 468 via `mult`), which is the filter-element
 * and per-channel PCM-input stride seen in the neighbouring
 * Sg2ExPcmInput{Ctrl,Close} records (.bss+0x9BFD8).  Operand order matters for
 * the two `addu`s: the index term must be written first, the channel term
 * second.  UNCONFIRMED: the record/element types.
 */
extern char D_kernel_bss_9BFD0[];

void Sg2ExPcmInputAutoFilterCtrl(unsigned int ch, int idx, int val) {
    if (ch < 4) {
        *(int *)(D_kernel_bss_9BFD0 + idx * 0xC4 + ch * 0x1D4) = val;
    }
}
