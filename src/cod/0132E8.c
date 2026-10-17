/* asm/cod/0132E8.s -> sceVif1PkAlign.
 * SCE libvifpk/libdma (cc=29)
 * MATCHED. */
void sceVif1PkAlign(unsigned int **a0, int a1, int a2) {
    unsigned int mask;
    unsigned int *p;
    unsigned int *end;

    mask = 0xFFFFFFFFu >> (32 - ((a1 + 2) & 0x1F));
    p = *a0;
    end = (unsigned int *)(((unsigned int)p & ~mask) + (a2 << 2));
    if (end < p)
        end = (unsigned int *)((unsigned int)end + (mask + 1));
    while (*a0 < end)
        *(*a0)++ = 0;
}
