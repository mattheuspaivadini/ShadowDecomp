/* asm/cod/013B60.s -> GS_CSR.
 * sceGsSyncV; VSync/VSync2 paths with the field bit computed as long before the interlace test (Session 22)
 * MATCHED. */
typedef unsigned long u_long;
typedef struct {
    short sceGsInterMode;   /* 0x00 */
    short sceGsOutMode;
    short sceGsFFMode;
    short sceGsVersion;
    int (*sceGsVSCfunc)(void);  /* 0x08 */
} sceGsGParam;

sceGsGParam *sceGsGetGParam(void);
int VSync(void);
long VSync2(void);
#define GS_CSR ((volatile u_long *)0x12001000)

int sceGsSyncV(void) {
    sceGsGParam *p = sceGsGetGParam();
    long r;

    if (p->sceGsVSCfunc == 0) {
        VSync();
        if (p->sceGsInterMode == 1)
            return (*GS_CSR >> 13) & 1;
        return 1;
    } else {
        r = (VSync2() >> 13) & 1;
        if (p->sceGsInterMode == 1)
            return r;
        return 1;
    }
}
