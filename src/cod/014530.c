/* asm/cod/014530.s -> func_00113520.
 * session9 R1 wcg wave
 * MATCHED (Session 8). */
struct S133970 {
    short f00;          /* 0x00 */
    short f02;          /* 0x02 */
    short f04;          /* 0x04 */
    short f06;          /* 0x06 */
    int   f08;          /* 0x08 */
};

struct GSDISPENV {                 /* 0x28 bytes */
    unsigned long long f00;        /* 0x00  PMODE   */
    unsigned long long f08;        /* 0x08  SMODE2  */
    unsigned long long f10;        /* 0x10  DISPFB  */
    unsigned long long f18;        /* 0x18  DISPLAY */
    unsigned long long f20;        /* 0x20  EXTDATA/BGCOLOR */
};

void *sceGsGetGParam(void);

void sceGsPutDispEnv(struct GSDISPENV *env) {
    struct S133970 *p = (struct S133970 *)sceGsGetGParam();

    if (p->f06 == 1) {
        *(volatile unsigned long long *)0x12000000u = env->f00;
        *(volatile unsigned long long *)0x12000070u = env->f10;
        *(volatile unsigned long long *)0x12000080u = env->f18;
        *(volatile unsigned long long *)0x120000C0u = env->f20;
    } else {
        *(volatile unsigned long long *)0x12000000u = env->f00;
        *(volatile unsigned long long *)0x12000020u = env->f08;
        *(volatile unsigned long long *)0x12000090u = env->f10;
        *(volatile unsigned long long *)0x120000A0u = env->f18;
        *(volatile unsigned long long *)0x120000E0u = env->f20;
    }
}
