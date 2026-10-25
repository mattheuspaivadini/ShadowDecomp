/* KERNEL.XFF @ 0x01B500 (36 B) - waitVscheduler
 * Evidence: sibling iosSendMsg(&.bss+0x7A1D0, 0, 1). UNCONFIRMED: queue name and iosSendMsg prototype.
 */
extern char D_kernel_bss_7A1D0[];
int iosSendMsg(void *queue, int msg, int mode);

void waitVscheduler(void) {
    iosSendMsg(D_kernel_bss_7A1D0, 0, 1);
}
