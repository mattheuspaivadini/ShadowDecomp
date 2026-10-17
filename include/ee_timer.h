/* ee_timer.h - the inline-asm system-time read shared by the SDK timer
 * routines of the boot image (iGetTimerSystemTime, GetTimerSystemTime). */
#ifndef EE_TIMER_H
#define EE_TIMER_H

/* UNCONFIRMED: the image computes the 64-bit system time with a hand-written
 * register sequence ($v1/$a0/$t0-$t2 used without saving, output register
 * chosen by the compiler: $v0 in iGetTimerSystemTime, $s0 across EIntr in
 * GetTimerSystemTime), i.e. an inline-asm block of the SDK's timer.c. This
 * reproduces it instruction for instruction:
 *   count = T2_COUNT; mode = T2_MODE; hi = D_00133918.base;
 *   if (mode & 0x800) { count = T2_COUNT; hi++; }   (overflow pending)
 *   r = (count | hi << 16) << ((mode & 3) ? 2 << (mode & 3) : 0); */
#define TIMER_SYSTEM_TIME(r)                                   \
    __asm__ volatile (                                          \
        ".set noreorder\n\t"                                    \
        "lui    $3, 0x1000\n\t"                                 \
        "lui    $4, %%hi(D_00133918)\n\t"                       \
        "ori    $3, $3, 0x1000\n\t"                             \
        "lwu    %0, 0($3)\n\t"                                  \
        "lw     $8, 0x10($3)\n\t"                               \
        "ld     $10, %%lo(D_00133918)($4)\n\t"                  \
        "andi   $9, $8, 0x800\n\t"                              \
        "beqz   $9, 1f\n\t"                                     \
        "addiu  $9, $0, 2\n\t"                                  \
        "lwu    %0, 0($3)\n\t"                                  \
        "daddiu $10, $10, 1\n"                                  \
        "1:\n\t"                                                \
        "andi   $8, $8, 3\n\t"                                  \
        "dsll   $10, $10, 16\n\t"                               \
        "movz   $9, $0, $8\n\t"                                 \
        "or     %0, %0, $10\n\t"                                \
        "dsllv  $9, $9, $8\n\t"                                 \
        "dsllv  %0, %0, $9\n\t"                                 \
        ".set reorder"                                          \
        : "=r" (r) : : "$3", "$4", "$8", "$9", "$10")

extern char D_00133918[];   /* timer state; +0x00 = 64-bit time base */

#endif /* EE_TIMER_H */
