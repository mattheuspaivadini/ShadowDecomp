/* KERNEL.XFF @ 0x016E58 (132 B) - func_016E58 (static, no symbol in the shipped .symtab)
 * STATUS: MATCHING [-G0 -fno-strict-aliasing] (scored 33/33 words, SIZE 132 B)
 * Evidence: jal isceGsPutIMR(0xFF00) keeps the result in $s0; u64 counter at .data+0x618
 * incremented (ld/daddiu/sd, volatile); hook at .data+0x62C called when non-NULL; GS register
 * 0x12001000 read-modify-write with |= 2; jal isceGsPutIMR($s0); `sync` + `ei` in one asm block
 * (the two-asm split gave a swapped epilogue pair); returns 0.
 * Levers tried: void return (SIZE 128, no `return 0`); two separate asm statements (2/33,
 *   ld $s0 scheduled after the return move); -fno-schedule-insns2 / -fno-schedule-insns / -fno-gcse
 *   on the split form; -g0 (8/33). The single asm "sync\n\tei" closed it.
 * UNCONFIRMED: function name, meaning of the hook and of the GS CSR bit 1 (0x12001000 |= 2).
 */
unsigned long isceGsPutIMR(unsigned long imr);
extern volatile unsigned long D_kernel_data_0618;
extern void (*D_kernel_data_062C)(void);

int func_016E58(void) {
    unsigned long saved = isceGsPutIMR(0xFF00);
    D_kernel_data_0618++;
    if (D_kernel_data_062C != 0) {
        D_kernel_data_062C();
    }
    *(volatile unsigned long *)0x12001000 |= 2;
    isceGsPutIMR(saved);
    __asm__ volatile ("sync\n\tei");
    return 0;
}
