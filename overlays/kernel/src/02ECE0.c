/* KERNEL.XFF @ 0x02ECE0 (72 B) - func_02ECE0 (static, no symbol in the shipped .symtab)
 * Evidence: first PCM input record (0x1D4 bytes at .bss+0x9BFD8) whose word +4 is 0, or -1. UNCONFIRMED: name.
 */
struct PcmInput {
    unsigned int status;
    int used;
    char pad8[0x1D4 - 8];
};
extern struct PcmInput D_kernel_bss_9BFD8[4];

int func_02ECE0(void) {
    int i;

    for (i = 0; i < 4; i++) {
        if (D_kernel_bss_9BFD8[i].used == 0) {
            return i;
        }
    }
    return -1;
}
