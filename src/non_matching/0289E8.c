/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 5 [cc=296].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/0289E8.s); this C
 * draft (Session 9) is kept for the record. */
extern int func_00129930(int a0, int a1, int a2);

struct S0289E8 {                 /* the pseudo-FILE built on the stack */
    char *p;                     /* 0x00 */
    int   r;                     /* 0x04 */
    int   w;                     /* 0x08 */
    short flags;                 /* 0x0C */
    short file;                  /* 0x0E */
    char *bf_base;               /* 0x10 */
    int   bf_size;               /* 0x14 */
    char  pad18[0x3C];
    int   field54;               /* 0x54: the real FILE */
};

int func_001289E8(int a0, char *buf, char *fmt, ...) {
    struct S0289E8 f;
    int n;

    f.field54 = a0;
    f.bf_base = buf;
    f.p = buf;
    f.flags = 0x208;
    f.bf_size = 0x7FFFFFFF;
    f.w = 0x7FFFFFFF;
    n = func_00129930((int)&f, (int)fmt, (int)((char *)&f + 0x98));
    *f.p = 0;
    return n;
}
