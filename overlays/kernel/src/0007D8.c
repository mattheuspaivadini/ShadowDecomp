/* KERNEL.XFF @ 0x0007D8 (36 B) - iosWaitIdleThread
 * Evidence: 0x10-byte frame saving $ra, sets $a0 = .bss + 0x8070 (HI16/LO16),
 * $a1 = 0, $a2 = 1, restores $ra and tail-jumps to iosSendMsg. The frame is
 * kept because the callee is reached with a sibling `j` after the restore.
 * UNCONFIRMED: the mailbox object's name; the boot-ELF `LoaderSys*` family
 * suggests a loader thread mailbox.
 */
extern unsigned long D_kernel_bss_8070;
int iosSendMsg(void *mailbox, int cmd, int wait);

void iosWaitIdleThread(void) {
    iosSendMsg(&D_kernel_bss_8070, 0, 1);
}
