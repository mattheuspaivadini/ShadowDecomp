/* func_00123158 @ 0x00123158 (0x24 bytes): return the inverted top bit of
 * func_00107380(). */
int func_00107380(void);

int func_00123158(void) {
    int r = func_00107380();

    r = ~r;
    return (unsigned)r >> 31;
}
