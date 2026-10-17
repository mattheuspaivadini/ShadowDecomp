/* asm/cod/013098.s -> sceVif1PkTerminate.
 * SCE libvifpk/libdma (cc=29)
 * MATCHED. */
typedef int u_long128 __attribute__ ((mode (TI)));

struct A00113098 {
    int  field00;   /* 0x00 current pointer */
    int  field04;   /* 0x04 */
    int  field08;   /* 0x08 saved block */
};

int sceVif1PkTerminate(struct A00113098 *a0) {
    int *p = (int *)a0->field00;
    struct A00113098 *s = (struct A00113098 *)a0->field08;

    while ((unsigned int)p & 0xC) {
        *p = 0;
        p++;
    }
    if (s) {
        int n = (u_long128 *)p - (u_long128 *)s - 1;
        s->field00 += n;
    }
    a0->field00 = (int)p;
    a0->field08 = 0;
    return (int)p;
}
