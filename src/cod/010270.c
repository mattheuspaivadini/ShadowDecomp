/* asm/cod/010270.s -> func_00110270 @ 0x00110270 (0x38 bytes)
 * Identical shape to func_0010FC08 (word copy of `size >> 2` words).
 */
int func_00110270(unsigned int *dst, unsigned int *src, unsigned int size) {
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
