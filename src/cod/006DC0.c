/* asm/cod/006DC0.s -> iSetAlarm @ 0x00106DC0 (0x10 bytes)
 * SCE libkernl syscall -0xFE (iSetAlarm) stub (00F360.c template).
 * no callers in this image; prototype UNCONFIRMED (ps2sdk kernel.h, time widened to int).
 * MATCHED. */
int iSetAlarm(int time, void *handler, void *arg) {
    register int v0 __asm__("$2");
    __asm__ __volatile__ ("addiu $3, $0, -0xFE\n\tsyscall" : "=r" (v0) : "r" (time), "r" (handler), "r" (arg) : "$3");
    return v0;
}
