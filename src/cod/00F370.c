/* asm/cod/00F370.s -> func_0010F370 @ 0x0010F370 (0x38 bytes)
 * Identical shape to func_0010FC08 (word copy of `size >> 2` words).
 */
int func_0010F370(unsigned int *dst, unsigned int *src, unsigned int size) {
    unsigned int i = 0;
    unsigned int count = size >> 2;

    if (count != 0) {
        do {
            *dst = *src;
            i++;
            src++;
            dst++;
        } while (i < count);
    }
    return 0;
}
