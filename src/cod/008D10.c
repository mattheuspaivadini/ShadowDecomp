/* asm/cod/008D10.s -> func_00108D10.
 * SCE snprintf output callback (Session 19)
 * MATCHED. */
int func_00108D10(char **pp, int *count, int c) {
    if (*count == 0)
        return 1;
    if (c < 0x100) {
        if (*count == 1)
            c = 0;
        *(*pp)++ = c;
        (*count)--;
        return 1;
    }
    **pp = 0;
    return 0;
}
