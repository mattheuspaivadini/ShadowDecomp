/* asm/cod/006DD0.s -> iReleaseAlarm @ 0x00106DD0 (0x10 bytes)
 * SCE libkernl syscall -0xFF (iReleaseAlarm) stub (00F360.c template).
 * no callers in this image; prototype UNCONFIRMED (ps2sdk kernel.h).
 * MATCHED. */
int iReleaseAlarm(int alarm_id) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, -0xFF\n\tsyscall" : "=r" (v0) : "r" (alarm_id) : "$3");
    return v0;
}
