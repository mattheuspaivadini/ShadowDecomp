/* KERNEL.XFF @ 0x02F6E0 (32 B) - Sg2ExPcmOutputAutoFilterInit
 * Evidence: sibling of the static filter initialiser at .text+0x2E608 with &.bss+0x9BE28 and mode.
 */
extern char D_kernel_bss_9BE28[];
void func_02E608(void *filter, int mode);

void Sg2ExPcmOutputAutoFilterInit(int mode) {
    func_02E608(D_kernel_bss_9BE28, mode);
}
