/* func_00123158 @ 0x00123158 (0x24 bytes): return the inverted top bit of
 * func_00107380(). */
int sceSifDmaStat(void);

int sceNetcnfifDmaCheck(void) {
    int r = sceSifDmaStat();

    r = ~r;
    return (unsigned)r >> 31;
}
