/* asm/cod/00FE50.s -> func_0010FE50 @ 0x0010FE50 (0x38 bytes)
 * Identical shape to func_0010FC08 (word copy of `size >> 2` words).
 */
int func_0010FE50(unsigned int *dst, unsigned int *src, unsigned int size) {
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
