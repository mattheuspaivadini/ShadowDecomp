/* asm/cod/0145F0.s -> sceGszbufaddr.
 * sceGszbufaddr; signed (x + 63) / 64 page counts (Session 22)
 * MATCHED. */
typedef unsigned long u_long;
void *sceGsGetGParam(void);

short sceGszbufaddr(short psm, short w, short h) {
    u_long *gp = (u_long *)sceGsGetGParam();
    int bw = (w + 63) / 64;
    int bh;
    if (psm & 2)
        bh = (h + 63) / 64;
    else
        bh = (h + 31) / 32;
    if ((*gp & 0x0000FFFF0000FFFFUL) == 1)
        return bw * bh;
    return bw * bh * 2;
}
