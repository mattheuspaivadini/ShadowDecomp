/* KERNEL.XFF @ 0x016DF0 (100 B) - iosWaitGPFinish
 * Evidence: polls the 64-bit counter at .data+0x618 until it advanced by n, calling isysSleepSubThread() (no args) each pass.
 * Levers: first param unused (n is a1); volatile long* p; loop-entry copies q/e forced by an empty asm "+r"(q),"+r"(e),"+r"(n)
 * (keeps n live so the sum lands in v1 with a1 first; operand order q,e gives move s1 before move s0).
 * c_sources: 016DF0 = src/016DF0.c -G0 -fno-strict-aliasing
 */
extern volatile long D_data_618;
void isysSleepSubThread(void);
void iosWaitGPFinish(volatile long *p, long n) {
    long t, e;
    volatile long *q;
    p = &D_data_618;
    t = n + *p;
    if (*p < t) {
        q = p; e = t;
        __asm__("" : "+r"(q), "+r"(e), "+r"(n));
        do {
            isysSleepSubThread();
        } while (*q < e);
    }
}
