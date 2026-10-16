/* asm/cod/010E00.s -> func_00110998.
 * Session 11a: asm memory barrier stops dbr annulling the store into the beqz delay
 * MATCHED (Session 8). */
struct N10E00 {
    struct N10E00 *next;            /* 0x00 */
    struct N10E00 *prev;            /* 0x04 */
    unsigned int   id;              /* 0x08 */
    unsigned int   flags;           /* 0x0C */
    unsigned long long f10;         /* 0x10 */
    unsigned long long f18;         /* 0x18 */
};

struct H10E00 {
    char pad00[0x10];
    unsigned int   count;           /* 0x10 */
    struct N10E00 *freehead;        /* 0x14 */
    struct N10E00 *head;            /* 0x18 */
    unsigned int   cur;             /* 0x1C */
};

extern struct H10E00 D_00133918;

void func_00110998(struct N10E00 *p);

unsigned int func_00110E00(int a0) {
    struct N10E00 *p;
    struct H10E00 *h;
    struct N10E00 *t;
    unsigned int f;
    unsigned int c;

    p = (struct N10E00 *)(((unsigned int)a0 >> 10) << 6);
    if (a0 < 0 || (a0 & 0x3FF) != p->id)
        return 0x80008002u;
    h = &D_00133918;
    if (h->cur == (unsigned int)a0)
        return 0x80000010u;
    f = p->flags;
    if (f & 2)
        func_00110998(p);
    __asm__ __volatile__ ("" : : : "memory");
    p->id = 0;
    p->flags = 0;
    t = h->freehead;
    c = h->count - 1;
    p->next = t;
    h->freehead = p;
    h->count = c;
    return 0;
}
