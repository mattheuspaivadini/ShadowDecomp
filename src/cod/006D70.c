/* asm/cod/006D70.s -> ReleaseAlarm @ 0x00106D70 (0x10 bytes)
 * SCE libkernl syscall 0xFD (ReleaseAlarm) stub (00F360.c template).
 * no callers in this image; prototype UNCONFIRMED (ps2sdk kernel.h).
 * MATCHED. */
int ReleaseAlarm(int alarm_id) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0xFD\n\tsyscall" : "=r" (v0) : "r" (alarm_id) : "$3");
    return v0;
}
