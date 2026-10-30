/* KERNEL.XFF @ 0x00C658 (292 B) - iosPopVu0Registers
 * Evidence: mirror of iosPushVu0Registers: frame 0x10 + saved ra, call to
 * iosDI, then two 31-register runs of lqc2 - the first from .bss+0xE0B0 in the
 * order vf5..vf7, vf1..vf4, vf8..vf31 (base $v1), the second from
 * .bss+0xDEB0 with a freshly materialised base ($v0) in plain vf1..vf31 order;
 * tail call to iosEI with the frame teardown in the jal delay slot.
 * UNCONFIRMED: prototypes of iosDI/iosEI; the identity of the .bss save area.
 * Notes for the lane: unlike the push side, the second block materialises its
 * own base (.bss+0xDEB0 = the first area - 0x200) instead of reusing the first
 * register, so the draft pins the first base to $3 and the second to $2.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));

void iosDI(void);
void iosEI(void);
extern u_long128 D_kernel_bss_E0B0[];
extern u_long128 D_kernel_bss_DEB0[];

void iosPopVu0Registers(void) {
    register u_long128 *p __asm__("$3");
    register u_long128 *q __asm__("$2");

    iosDI();
    p = D_kernel_bss_E0B0;
    __asm__ __volatile__(
        "lqc2 $vf5, 0x0(%0)\n"
        "lqc2 $vf6, 0x10(%0)\n"
        "lqc2 $vf7, 0x20(%0)\n"
        "lqc2 $vf1, 0x30(%0)\n"
        "lqc2 $vf2, 0x40(%0)\n"
        "lqc2 $vf3, 0x50(%0)\n"
        "lqc2 $vf4, 0x60(%0)\n"
        "lqc2 $vf8, 0x70(%0)\n"
        "lqc2 $vf9, 0x80(%0)\n"
        "lqc2 $vf10, 0x90(%0)\n"
        "lqc2 $vf11, 0xA0(%0)\n"
        "lqc2 $vf12, 0xB0(%0)\n"
        "lqc2 $vf13, 0xC0(%0)\n"
        "lqc2 $vf14, 0xD0(%0)\n"
        "lqc2 $vf15, 0xE0(%0)\n"
        "lqc2 $vf16, 0xF0(%0)\n"
        "lqc2 $vf17, 0x100(%0)\n"
        "lqc2 $vf18, 0x110(%0)\n"
        "lqc2 $vf19, 0x120(%0)\n"
        "lqc2 $vf20, 0x130(%0)\n"
        "lqc2 $vf21, 0x140(%0)\n"
        "lqc2 $vf22, 0x150(%0)\n"
        "lqc2 $vf23, 0x160(%0)\n"
        "lqc2 $vf24, 0x170(%0)\n"
        "lqc2 $vf25, 0x180(%0)\n"
        "lqc2 $vf26, 0x190(%0)\n"
        "lqc2 $vf27, 0x1A0(%0)\n"
        "lqc2 $vf28, 0x1B0(%0)\n"
        "lqc2 $vf29, 0x1C0(%0)\n"
        "lqc2 $vf30, 0x1D0(%0)\n"
        "lqc2 $vf31, 0x1E0(%0)\n"
        : : "r"(p) : "memory");
    q = D_kernel_bss_DEB0;
    __asm__ __volatile__(
        "lqc2 $vf1, 0x0(%0)\n"
        "lqc2 $vf2, 0x10(%0)\n"
        "lqc2 $vf3, 0x20(%0)\n"
        "lqc2 $vf4, 0x30(%0)\n"
        "lqc2 $vf5, 0x40(%0)\n"
        "lqc2 $vf6, 0x50(%0)\n"
        "lqc2 $vf7, 0x60(%0)\n"
        "lqc2 $vf8, 0x70(%0)\n"
        "lqc2 $vf9, 0x80(%0)\n"
        "lqc2 $vf10, 0x90(%0)\n"
        "lqc2 $vf11, 0xA0(%0)\n"
        "lqc2 $vf12, 0xB0(%0)\n"
        "lqc2 $vf13, 0xC0(%0)\n"
        "lqc2 $vf14, 0xD0(%0)\n"
        "lqc2 $vf15, 0xE0(%0)\n"
        "lqc2 $vf16, 0xF0(%0)\n"
        "lqc2 $vf17, 0x100(%0)\n"
        "lqc2 $vf18, 0x110(%0)\n"
        "lqc2 $vf19, 0x120(%0)\n"
        "lqc2 $vf20, 0x130(%0)\n"
        "lqc2 $vf21, 0x140(%0)\n"
        "lqc2 $vf22, 0x150(%0)\n"
        "lqc2 $vf23, 0x160(%0)\n"
        "lqc2 $vf24, 0x170(%0)\n"
        "lqc2 $vf25, 0x180(%0)\n"
        "lqc2 $vf26, 0x190(%0)\n"
        "lqc2 $vf27, 0x1A0(%0)\n"
        "lqc2 $vf28, 0x1B0(%0)\n"
        "lqc2 $vf29, 0x1C0(%0)\n"
        "lqc2 $vf30, 0x1D0(%0)\n"
        "lqc2 $vf31, 0x1E0(%0)\n"
        : : "r"(q) : "memory");
    iosEI();
}
