/* asm/cod/010430.s -> InitTimer.
 * libkernel timer init: 128-entry alarm free list, INTC 11 handler, T2_MODE read into a local and or-ed step by step
 * MATCHED. */
#include "symbols.h"

struct TimerAlarm {             /* 0x40-byte alarm pool entry */
    struct TimerAlarm *next;    /* 0x00 free-list link */
    char rest[0x3C];
};

struct TimerState {
    long long base;             /* 0x00 */
    int       f08;              /* 0x08 INTC handler id */
    int       f0C;              /* 0x0C */
    volatile int f10;           /* 0x10 */
    struct TimerAlarm *free;    /* 0x14 */
};

extern struct TimerState D_00133918;
extern struct TimerAlarm D_00148880[128];

void *func_001283D0(void *dst, int c, unsigned int size);   /* memset */
int  _InitAlarm(void);
int  AddIntcHandler2(int cause, int (*handler)(int, void *, void *), int next, void *arg);
int  func_001109D0(int cause, void *arg, void *addr);
int  DIntr(void);
int  EIntr(void);
void SetT2_COUNT(int a0);
void SetT2_COMP(int a0);
void SetT2_MODE(int a0);
int  EnableIntc(int cause);

int InitTimer(int mode) {
    int i;
    int h;
    int g;
    unsigned int m;

    if (D_00133918.f08 >= 0)
        return 0x80008001;
    D_00133918.base = 0;
    D_00133918.f10 = 0;
    func_001283D0(D_00148880, 0, 0x2000);
    D_00133918.free = D_00148880;
    for (i = 127; i >= 0; i--)
        D_00148880[i].next = &D_00148880[i + 1];
    D_00148880[127].next = 0;
    _InitAlarm();
    h = AddIntcHandler2(0xB, func_001109D0, 0, 0);
    if (h < 0)
        return 0x80009021;
    D_00133918.f08 = h;
    g = DIntr();
    m = HWREG(EE_T2_MODE);
    m = (m & ~3) | mode;
    m |= 0x300;
    if (!(m & 0x80)) {
        SetT2_COUNT(0);
        m |= 0xC80;
        SetT2_COMP(0xFFFF);
    }
    SetT2_MODE(m);
    EnableIntc(0xB);
    if (g != 0)
        EIntr();
    return 0;
}
