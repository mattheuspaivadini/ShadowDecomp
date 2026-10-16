/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 3 [cc=296].
 * stack/store-order: pseudo-FILE field stores + arg area (&f+0x90, 0xC0 frame); wave4c (R1)
 * The original .s stays in the build (asm/cod/028A70.s); this C
 * draft (Session 8) is kept for the record. */
extern __attribute__((section(".data"))) int _impure_ptr;   /* lui/%lo scalar */
int func_00129930(int a0, int a1, int a2);

struct S028A70 {              /* the pseudo-FILE built on the stack */
    char *p;                  /* 0x00  _p     */
    int   r;                  /* 0x04  _r     */
    int   w;                  /* 0x08  _w     */
    short flags;              /* 0x0C  _flags */
    short file;               /* 0x0E  _file  */
    char *bf_base;            /* 0x10  _bf._base */
    int   bf_size;            /* 0x14  _bf._size */
    char  pad18[0x3C];
    int   field54;            /* 0x54  the real FILE */
};

int func_00128A70(char *buf, char *fmt, ...) {
    struct S028A70 f;
    int n;

    f.p = buf;
    f.bf_base = buf;
    f.w = 0x7FFFFFFF;
    f.bf_size = 0x7FFFFFFF;
    f.flags = 0x208;
    f.field54 = _impure_ptr;
    n = func_00129930((int)&f, (int)fmt, (int)((char *)&f + 0x90));
    *f.p = 0;
    return n;
}
