/* asm/cod/011FD0.s -> sbrk.
 * SCE libkernl sbrk: grows the heap end D_00133944 under the SCE `DI' idiom
 * (read Status.EIE; if set, di/sync.p until it reads clear) and fails with
 * ENOMEM past EndOfHeap(). di and sync.p are separate asm statements: as one
 * asm the loop looks one insn shorter and gets the R5900 short-loop nop.
 * MATCHED. */
extern char *D_00133944 __attribute__((section(".data")));   /* the heap end */

char *EndOfHeap(void);
int *__errno(void);

void *sbrk(int incr) {
    char *end;
    int stat;
    int intr;

    __asm__ __volatile__ ("mfc0 %0, $12" : "=r" (intr));
    intr &= 0x10000;
    if (intr) {
        do {
            __asm__ __volatile__ ("di");
            __asm__ __volatile__ ("sync.p");
            __asm__ __volatile__ ("mfc0 %0, $12" : "=r" (stat));
        } while (stat & 0x10000);
    }
    end = D_00133944 + incr;
    if (EndOfHeap() < end) {
        *__errno() = 12;    /* ENOMEM */
        if (intr)
            __asm__ __volatile__ ("ei");
        return (void *)0xFFFFFFFF;
    }
    {
        char *prev = D_00133944;
        D_00133944 = end;
        if (intr)
            __asm__ __volatile__ ("ei");
        return prev;
    }
}
