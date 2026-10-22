/* asm/cod/0109D0.s -> func_001109D0.
 * SCE libkernl timer INTC 11 handler (registered by InitTimer 010430): while
 * the T2 compare flag is set, pop every alarm of the sorted list (010910 key
 * f20 + f10 - f18) that is due, call its handler with its own $gp, and free
 * (-1), disarm (0) or re-arm it (+max(r, 0x3999)); then re-program the compare
 * (func_00110780) and ei. get_time() is the 64-bit system-time read with the
 * overflow fix-up; the time base is read volatile but its increment is a plain
 * store (it fills the SetT2_MODE slot), and the in-use count is volatile (its
 * store stays out of the free-path b slot), as in EndTimer 010588.
 * MATCHED. */
#include "symbols.h"

struct N109D0 {
    struct N109D0 *next;            /* 0x00 */
    struct N109D0 *prev;            /* 0x04 */
    unsigned int   f08;             /* 0x08 */
    unsigned int   f0C;             /* 0x0C */
    unsigned long long f10;         /* 0x10 */
    unsigned long long f18;         /* 0x18 */
    unsigned long long f20;         /* 0x20 */
    unsigned long long (*handler)(unsigned int, unsigned long long, unsigned long long, void *, void *); /* 0x28 */
    void          *gp;              /* 0x2C */
    void          *arg;             /* 0x30 */
};

struct D109D0 {
    volatile unsigned long long base;   /* 0x00 */
    int            f08;             /* 0x08 */
    int            f0C;             /* 0x0C */
    volatile int   f10;             /* 0x10 */
    struct N109D0 *f14;             /* 0x14 */
    struct N109D0 *head;            /* 0x18 */
    int            f1C;             /* 0x1C */
};

extern struct D109D0 D_00133918;

void SetT2_MODE(int a0);
struct N109D0 *func_00110998(struct N109D0 *n);
void func_00110910(struct N109D0 *n);
void func_00110780(unsigned long long now);

static __inline__ unsigned long long get_time(void) {
    unsigned int count = HWREG(EE_T2_COUNT);
    unsigned int mode = HWREG(EE_T2_MODE);

    if (mode & 0x800) {
        *(unsigned long long *)&D_00133918.base = D_00133918.base + 1;
        SetT2_MODE(mode & ~0x400);
        count = HWREG(EE_T2_COUNT);
    }
    return ((D_00133918.base << 16) | count) << ((mode & 3) * 4);
}

int func_001109D0(int ca, void *a1, void *a2) {
    struct N109D0 *n;
    struct N109D0 *next;
    unsigned long long now;
    unsigned long long t;
    unsigned long long r;

    if (HWREG(EE_T2_MODE) & 0x400) {
        n = D_00133918.head;
        while (n) {
            unsigned long long key = n->f20 + n->f10 - n->f18;

            now = get_time();
            if (now < key)
                break;
            next = func_00110998(n);
            t = now + n->f18 - n->f10;
            D_00133918.f1C = ((unsigned int)n << 4) | n->f08;
            __asm__ __volatile__ ("lw $28, %0" : : "m" (n->gp));
            r = n->handler(((unsigned int)n << 4) | n->f08, n->f20, t, n->arg, a2);
            if (r == 0) {
                n->f0C &= ~2;
            } else if (r == -1) {
                n->f08 = 0;
                n->f0C = 0;
                n->next = D_00133918.f14;
                D_00133918.f14 = n;
                D_00133918.f10--;
            } else {
                if (r < 0x3999)
                    r = 0x3999;
                n->f20 += r;
                func_00110910(n);
            }
            n = next;
        }
    }
    D_00133918.f1C = -1;
    func_00110780(get_time());
    get_time();
    __asm__ __volatile__ ("sync");
    __asm__ __volatile__ ("ei");
    return 0;
}
