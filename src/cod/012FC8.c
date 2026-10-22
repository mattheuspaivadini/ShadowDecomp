/* asm/cod/012FC8.s -> sceSifWriteBackDCache @ 0x00112FC8 (0xAC bytes, 43 insns)
 * SCE sifcmd cache writeback helper: align range [ptr, ptr+size-1] to 64-byte
 * cache lines, then writeback-invalidate (cache 0x18) first mod-8 lines and
 * then unrolled blocks of 8 lines.
 * MATCHED. */
void sceSifWriteBackDCache(void *ptr, int size) {
    register unsigned int mask __asm__("$25");
    register unsigned int p __asm__("$8");
    register unsigned int r __asm__("$9");
    register unsigned int q __asm__("$10");
    register unsigned int n __asm__("$11");

    __asm__ __volatile__ ("li %0, 0xFFFFFFC0" : "=r" (mask));
    if (size <= 0)
        return;
    q = (unsigned int)ptr + size;
    p = (unsigned int)ptr & mask;
    q = q - 1;
    r = q & mask;
    __asm__ ("" : "+r" (r));
    q = r - p;
    n = q >> 6;
    __asm__ ("" : "+r" (n));
    n = n + 1;
    r = n & 7;
    __asm__ __volatile__ (
        ".set noreorder\n\t"
        "beqz %1, 2f\n\t"
        " srl %2, %3, 3\n"
        "1:\n\t"
        "sync\n\t"
        "cache 0x18, 0x0(%0)\n\t"
        "sync\n\t"
        "nop\n\t"
        "addiu %1, %1, -1\n\t"
        "bgtz %1, 1b\n\t"
        " addiu %0, %0, 0x40\n"
        "2:\n\t"
        "beqz %2, 4f\n"
        "3:\n\t"
        " addiu %2, %2, -1\n\t"
        "sync\n\t"
        "cache 0x18, 0x0(%0)\n\t"
        "sync\n\t"
        "cache 0x18, 0x40(%0)\n\t"
        "sync\n\t"
        "cache 0x18, 0x80(%0)\n\t"
        "sync\n\t"
        "cache 0x18, 0xC0(%0)\n\t"
        "sync\n\t"
        "cache 0x18, 0x100(%0)\n\t"
        "sync\n\t"
        "cache 0x18, 0x140(%0)\n\t"
        "sync\n\t"
        "cache 0x18, 0x180(%0)\n\t"
        "sync\n\t"
        "cache 0x18, 0x1C0(%0)\n\t"
        "sync\n\t"
        "bgtz %2, 3b\n\t"
        " addiu %0, %0, 0x200\n"
        "4:\n\t"
        ".set reorder"
        : "+r" (p), "+r" (r), "=r" (q) : "r" (n) : "memory"
    );
}
