/* asm/cod/010FA0.s -> func_00110C78.
 * Session 11a: empty-asm +r pin forces D_00133918 base materialisation
 * MATCHED (Session 8). */
struct N10FA0 {
    struct N10FA0 *next;            /* 0x00 */
    struct N10FA0 *prev;            /* 0x04 */
    unsigned int   id;              /* 0x08 */
    unsigned int   flags;           /* 0x0C */
    unsigned long long f10;         /* 0x10 */
    unsigned long long f18;         /* 0x18 */
};

struct H10FA0 {
    char pad00[0x10];
    unsigned int   count;           /* 0x10 */
    struct N10FA0 *freehead;        /* 0x14 */
    struct N10FA0 *head;            /* 0x18 */
    unsigned int   cur;             /* 0x1C */
};

extern struct H10FA0 D_00133918;

unsigned long long iGetTimerSystemTime(void);
void func_00110910(struct N10FA0 *n);
void func_00110780(unsigned long long t);

unsigned int iStartTimerCounter(int a0) {
    struct N10FA0 *p;
    struct H10FA0 *h;
    unsigned int f;
    unsigned long long t;

    p = (struct N10FA0 *)(((unsigned int)a0 >> 10) << 6);
    if (a0 < 0 || (a0 & 0x3FF) != p->id)
        return 0x80008002u;
    h = &D_00133918;
    asm volatile ("" : "+r" (h));
    if (h->cur == (unsigned int)a0)
        return 0x80000010u;
    if (p->flags & 1)
        return 1;
    t = iGetTimerSystemTime();
    f = p->flags;
    p->f10 = t;
    f |= 1;
    p->flags = f;
    if (f & 2) {
        func_00110910(p);
        func_00110780(t);
    }
    return 0;
}
