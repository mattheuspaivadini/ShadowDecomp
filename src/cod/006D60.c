/* asm/cod/006D60.s -> SetAlarm @ 0x00106D60 (0x10 bytes)
 * SCE libkernl syscall 0xFC (SetAlarm) stub (00F360.c template).
 * no callers in this image; prototype UNCONFIRMED (ps2sdk kernel.h, time widened to int).
 * MATCHED. */
int SetAlarm(int time, void *handler, void *arg) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, 0xFC\n\tsyscall" : "=r" (v0) : "r" (time), "r" (handler), "r" (arg) : "$3");
    return v0;
}
