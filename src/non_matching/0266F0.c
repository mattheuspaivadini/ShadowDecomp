/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 33 [cc=296].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/0266F0.s); this C
 * draft (Session 9) is kept for the record. */
struct In0266F0 {
    int f0;                 /* 0x00 */
    int f4;                 /* 0x04 */
};

struct Out0266F0 {
    char *f0;               /* 0x00 */
    int   f4;               /* 0x04 */
    int   f8;               /* 0x08 */
    int   fC;               /* 0x0C */
    int   f10;              /* 0x10 */
};

extern char D_00139250[];       /* ""   */
extern char D_00139258[];       /* "eh" */
extern int func_00128E6C(char *p, char *s);
extern int func_001290C4(char *p);
extern unsigned char *func_00125998(unsigned char *p, int *out);
extern unsigned char *func_001259E0(unsigned char *p, int *out);

unsigned char *func_001266F0(struct In0266F0 *x, struct Out0266F0 *s) {
    char *p;
    char *q;
    unsigned char *r;
    int n;

    p = (char *)x - x->f4 + 0xD;
    s->f0 = p;
    if (func_00128E6C(p, D_00139250) != 0 &&
        func_00128E6C(p, D_00139258) != 0 &&
        *p != 0x7A)
        return 0;
    q = p + func_001290C4(p);
    r = (unsigned char *)(q + 1);
    if (func_00128E6C(p, D_00139258) != 0) {
        s->f4 = 0;
    } else {
        s->f4 = *(int *)r;
        r = (unsigned char *)(q + 5);
    }
    r = func_00125998(r, &s->f8);
    r = func_001259E0(r, &s->fC);
    s->f10 = *r;
    r++;
    if (*(char *)s->f0 == 0x7A) {
        r = func_00125998(r, &n);
        r = (unsigned char *)(r + n);
    }
    return r;
}
