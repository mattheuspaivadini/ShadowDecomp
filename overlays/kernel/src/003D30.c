/* KERNEL.XFF @ 0x003D30 (44 B) - func_003D30 (static, no symbol in the shipped .symtab)
 * Evidence: whole-body inline asm: sync.l, then five nops polled with bc0f until the COP0 condition is set (waits for the DMA/CPCOND0 flag); GCC adds the jr. UNCONFIRMED: name and purpose.
 */
void func_003D30(void) {
    __asm__ __volatile__(
        "\tsync.l\n"
        "1:\n"
        "\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n"
        "\tbc0f 1b\n"
        "\tnop\n");
}
