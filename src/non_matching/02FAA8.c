/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 11 [cc=296].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/02FAA8.s); this C
 * draft (Session 9) is kept for the record. */
struct S02FAA8 {
    char pad00[0x0C];
    unsigned short f0C;          /* 0x0C status word, 0x100 flushed / 0x1000 ok */
    short f0E;                   /* 0x0E signed halfword handle argument */
    char pad10[0x44];
    int f54;                     /* 0x54 handle passed to the worker */
};

extern void _lseek_r(int a0, int a1, int a2, int a3);
extern long long _write_r(int a0, int a1, int a2, int a3);

int __swrite(struct S02FAA8 *p, int a1, int a2) {
    if ((p->f0C & 0x100) != 0)
        _lseek_r(p->f54, p->f0E, 0, 2);
    p->f0C &= 0xEFFF;
    return (int)_write_r(p->f54, p->f0E, a1, a2);
}
/* func_0012FAA8 */
