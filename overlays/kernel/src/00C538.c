/* KERNEL.XFF @ 0x00C538 (288 B) - iosPushVu0Registers
 * Evidence: frame 0x10 + saved ra, call to iosDI, then two 31-register runs of
 * sqc2: the first at .bss+0xE0B0 in the order vf5..vf7, vf1..vf4, vf8..vf31
 * (base in $v1), then $v1 -= 0x200 and a plain vf1..vf31 run; tail call to
 * iosEI with the frame teardown in the jal delay slot.
 * UNCONFIRMED: prototypes of iosDI/iosEI; the identity of the .bss save area.
 * Notes for the lane: the base has to be a `register ... asm("$3")` variable and
 * the address assignment must follow the iosDI() call (declaring it at the top
 * keeps it in a callee-saved register across the call); the second run reuses
 * the same register through the `addiu %0,%0,-0x200` inside the asm.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));

void iosDI(void);
void iosEI(void);
extern u_long128 D_kernel_bss_E0B0[];

void iosPushVu0Registers(void) {
    register u_long128 *p __asm__("$3");

    iosDI();
    p = D_kernel_bss_E0B0;
    __asm__ __volatile__(
        "sqc2 $vf5, 0x0(%0)\n"
        "sqc2 $vf6, 0x10(%0)\n"
        "sqc2 $vf7, 0x20(%0)\n"
        "sqc2 $vf1, 0x30(%0)\n"
        "sqc2 $vf2, 0x40(%0)\n"
        "sqc2 $vf3, 0x50(%0)\n"
        "sqc2 $vf4, 0x60(%0)\n"
        "sqc2 $vf8, 0x70(%0)\n"
        "sqc2 $vf9, 0x80(%0)\n"
        "sqc2 $vf10, 0x90(%0)\n"
        "sqc2 $vf11, 0xA0(%0)\n"
        "sqc2 $vf12, 0xB0(%0)\n"
        "sqc2 $vf13, 0xC0(%0)\n"
        "sqc2 $vf14, 0xD0(%0)\n"
        "sqc2 $vf15, 0xE0(%0)\n"
        "sqc2 $vf16, 0xF0(%0)\n"
        "sqc2 $vf17, 0x100(%0)\n"
        "sqc2 $vf18, 0x110(%0)\n"
        "sqc2 $vf19, 0x120(%0)\n"
        "sqc2 $vf20, 0x130(%0)\n"
        "sqc2 $vf21, 0x140(%0)\n"
        "sqc2 $vf22, 0x150(%0)\n"
        "sqc2 $vf23, 0x160(%0)\n"
        "sqc2 $vf24, 0x170(%0)\n"
        "sqc2 $vf25, 0x180(%0)\n"
        "sqc2 $vf26, 0x190(%0)\n"
        "sqc2 $vf27, 0x1A0(%0)\n"
        "sqc2 $vf28, 0x1B0(%0)\n"
        "sqc2 $vf29, 0x1C0(%0)\n"
        "sqc2 $vf30, 0x1D0(%0)\n"
        "sqc2 $vf31, 0x1E0(%0)\n"
        "addiu %0, %0, -0x200\n"
        "sqc2 $vf1, 0x0(%0)\n"
        "sqc2 $vf2, 0x10(%0)\n"
        "sqc2 $vf3, 0x20(%0)\n"
        "sqc2 $vf4, 0x30(%0)\n"
        "sqc2 $vf5, 0x40(%0)\n"
        "sqc2 $vf6, 0x50(%0)\n"
        "sqc2 $vf7, 0x60(%0)\n"
        "sqc2 $vf8, 0x70(%0)\n"
        "sqc2 $vf9, 0x80(%0)\n"
        "sqc2 $vf10, 0x90(%0)\n"
        "sqc2 $vf11, 0xA0(%0)\n"
        "sqc2 $vf12, 0xB0(%0)\n"
        "sqc2 $vf13, 0xC0(%0)\n"
        "sqc2 $vf14, 0xD0(%0)\n"
        "sqc2 $vf15, 0xE0(%0)\n"
        "sqc2 $vf16, 0xF0(%0)\n"
        "sqc2 $vf17, 0x100(%0)\n"
        "sqc2 $vf18, 0x110(%0)\n"
        "sqc2 $vf19, 0x120(%0)\n"
        "sqc2 $vf20, 0x130(%0)\n"
        "sqc2 $vf21, 0x140(%0)\n"
        "sqc2 $vf22, 0x150(%0)\n"
        "sqc2 $vf23, 0x160(%0)\n"
        "sqc2 $vf24, 0x170(%0)\n"
        "sqc2 $vf25, 0x180(%0)\n"
        "sqc2 $vf26, 0x190(%0)\n"
        "sqc2 $vf27, 0x1A0(%0)\n"
        "sqc2 $vf28, 0x1B0(%0)\n"
        "sqc2 $vf29, 0x1C0(%0)\n"
        "sqc2 $vf30, 0x1D0(%0)\n"
        "sqc2 $vf31, 0x1E0(%0)\n"
        : "+r"(p) : : "memory");
    iosEI();
}
