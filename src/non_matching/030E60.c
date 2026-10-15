/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 27 [cc=296].
 * session9 R2 waveA; residual class not auto-classified
 * The original .s stays in the build (asm/cod/030E60.s); this C
 * draft (Session 9) is kept for the record. */
struct F30E60 {
    char           *p;        /* 0x00 _p                        */
    int             r;        /* 0x04 _r                        */
    int             w;        /* 0x08 _w                        */
    unsigned short  flags;    /* 0x0C _flags                    */
    short           file;     /* 0x0E _file                     */
    char           *bf_base;  /* 0x10 _bf._base                 */
    int             bf_size;  /* 0x14 _bf._size                 */
    int             f18;      /* 0x18                           */
    char            pad1C[0x14];
    char           *u_base;   /* 0x30 the 3-byte pushback base  */
    int             u_size;   /* 0x34 its size                  */
    int             f38;      /* 0x38 saved _p                  */
    int             f3C;      /* 0x3C saved _r                  */
    char            buf40[2]; /* 0x40 pushback bytes            */
    char            c42;      /* 0x42 the pushed byte           */
    char            pad43[0x11];
    int             dev54;    /* 0x54 the device handle         */
};

extern int  D_00135C60[];   /* .data, non-small -> lui/%lo */
extern void func_0012DA00(int dev);
extern int  func_0012D6D8(struct F30E60 *p);
extern int  func_00130D78(struct F30E60 *p);

int func_00130E60(int c, struct F30E60 *p) {
    int r;
    char *q;

    if (c == -1)
        return -1;
    if (p->dev54 == 0)
        p->dev54 = D_00135C60[0];
    if (*(int *)(p->dev54 + 0x38) == 0)
        func_0012DA00(p->dev54);
    p->flags = (unsigned short)(p->flags & 0xFFDF);
    if (!(p->flags & 4)) {
        if (!(p->flags & 0x10))
            return -1;
        if (p->flags & 8) {
            r = func_0012D6D8(p);
            if (r != 0)
                return -1;
            p->w = 0;
            p->f18 = 0;
            p->flags = (unsigned short)(p->flags & 0xFFF7);
        }
        p->flags = (unsigned short)(p->flags | 4);
    }
    c = c & 0xFF;
    if (p->u_base != 0) {
        if (p->r >= p->u_size) {
            r = func_00130D78(p);
            if (r != 0)
                return -1;
        }
        q = p->p;
        q = q - 1;
        p->p = q;
        *q = (char)c;
        p->r = p->r + 1;
        return c;
    }
    if (p->bf_base != 0
        && (unsigned int)p->bf_base < (unsigned int)p->p
        && *((unsigned char *)p->p - 1) == (unsigned char)c) {
        p->p = p->p - 1;
        p->r = p->r + 1;
        return c;
    }
    p->f3C = p->r;
    p->f38 = (int)p->p;
    p->u_base = (char *)p + 0x40;
    p->u_size = 3;
    p->p = (char *)p + 0x42;
    p->c42 = (char)c;
    p->r = 1;
    return c;
}
