/* v10: barrier after the quadword store forces the field stores to stay after */
typedef unsigned int u_long128 __attribute__((mode(TI)));

struct S {
    u_long128 *write;
    char pad04[0x10];
    u_long128 *last;
};

void sceVif1PkOpenGifTag(struct S *p, u_long128 value) {
    u_long128 *q = p->write;
    u_long128 *next = q + 1;

    *q = value;
    __asm__ __volatile__("" ::: "memory");
    p->write = next;
    __asm__ __volatile__("" ::: "memory");
    p->last = q;
}
