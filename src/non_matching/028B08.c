/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 20 [cc=296].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/028B08.s); this C
 * draft (Session 9) is kept for the record. */
extern int D_00135C60[];         /* .data 0x00135C60: lui/%lo (non-small) */
extern int func_001290C4(char *s);
extern int func_0012B2B8(int a0, int a1, int a2, int a3);
int func_00128B00(void);

struct S028B08 {                 /* the pseudo-FILE built on the stack */
    char *p;                     /* 0x00 */
    int   r;                     /* 0x04: characters still available */
    int   w;                     /* 0x08 */
    short flags;                 /* 0x0C */
    short file;                  /* 0x0E */
    char *bf_base;               /* 0x10 */
    int   bf_size;               /* 0x14: strlen(buf) */
    char  pad18[8];
    int   field20;               /* 0x20: the putc callback func_00128B00 */
    char  pad24[0xC];
    int   field30;               /* 0x30 */
    char  pad34[0x10];
    int   field44;               /* 0x44 */
    char  pad48[0xC];
    int   field54;               /* 0x54: the real FILE */
};

int func_00128B08(char *buf, char *fmt, ...) {
    struct S028B08 f;
    int n;

    f.bf_base = buf;
    f.p = buf;
    n = func_001290C4(buf);
    f.flags = 4;
    f.bf_size = n;
    f.field20 = (int)func_00128B00;
    f.field54 = D_00135C60[0];
    f.r = n;
    f.field30 = 0;
    f.field44 = 0;
    return func_0012B2B8((int)&f, (int)fmt, (int)((char *)&f + 0x90),
                         D_00135C60[0]);
}
