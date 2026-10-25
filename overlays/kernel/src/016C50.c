/* KERNEL.XFF @ 0x016C50 (60 B) - iosChkGpDlTransExec
 * Evidence: busy if bit 8 of 0x10009000 (VIF1_STAT) or of 0x1000A000 (GIF_STAT) is set; a short-circuit OR gives the two bnel with the busy=1 slot.
 */
int iosChkGpDlTransExec(void) {
    int busy = 0;

    if ((*(volatile int *)0x10009000 & 0x100) || (*(volatile int *)0x1000A000 & 0x100)) {
        busy = 1;
    }
    return busy;
}
