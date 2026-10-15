/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 33 [cc=29].
 * session9 R2 waveA; residual class not auto-classified
 * The original .s stays in the build (asm/cod/013598.s); this C
 * draft (Session 9) is kept for the record. */
struct D13598 {
    unsigned long long q00;   /* 0x00 FRAME_1 data   */
    unsigned long long q08;   /* 0x08 id 0x4C        */
    unsigned long long q10;   /* 0x10 ZBUF_1 data    */
    unsigned long long q18;   /* 0x18 id 0x4E        */
    unsigned long long q20;   /* 0x20 XYOFFSET data  */
    unsigned long long q28;   /* 0x28 id 0x18        */
    unsigned long long q30;   /* 0x30 SCISSOR data   */
    unsigned long long q38;   /* 0x38 id 0x40        */
    unsigned long long q40;   /* 0x40 PRMODECONT data*/
    unsigned long long q48;   /* 0x48 id 0x1A        */
    unsigned long long q50;   /* 0x50 COLCLAMP data  */
    unsigned long long q58;   /* 0x58 id 0x46        */
    unsigned long long q60;   /* 0x60 DTHE data      */
    unsigned long long q68;   /* 0x68 id 0x45        */
    unsigned long long q70;   /* 0x70 TEST_1 data    */
    unsigned long long q78;   /* 0x78 id 0x47        */
};

extern int func_001145F0(short a0, short a1, short a2);

int func_00113598(struct D13598 *p, short a1, short a2, short a3, short a4,
                  short a5) {
    unsigned long long fbw;
    unsigned long long v;

    fbw = (a2 + 0x3F) >> 6;
    p->q08 = 0x4C;
    p->q00 = ((fbw & 0x3F) << 16) | ((unsigned long long)(a1 & 0xF) << 24);
    p->q18 = 0x4E;
    if (a4 == 0)
        v = ((unsigned long long)(int)func_001145F0(a1, a2, a3)
             | ((unsigned long long)(a5 & 0xF) << 24)
             | 0x100000000ULL);
    else
        v = ((unsigned long long)(int)func_001145F0(a1, a2, a3)
             | ((unsigned long long)(a5 & 0xF) << 24));
    p->q10 = v;
    p->q20 = (((0x800 - (long long)(a2 >> 1)) << 4)
              | ((0x800 - (long long)(a3 >> 1)) << 36));
    p->q28 = 0x18;
    p->q30 = (((long long)(a2 - 1) << 16) | ((long long)(a3 - 1) << 48));
    p->q38 = 0x40;
    p->q40 = p->q40 | 1;
    p->q48 = 0x1A;
    p->q50 = p->q50 | 1;
    p->q58 = 0x46;
    if (a1 & 2)
        p->q60 = p->q60 | 1;
    else
        p->q60 = p->q60 & ~1ULL;
    p->q68 = 0x45;
    if (a4 != 0)
        p->q70 = ((unsigned long long)(a4 & 3) << 17) | 0x10000;
    else
        p->q70 = 0x30000;
    p->q78 = 0x47;
    __asm__ __volatile__("sync" ::: "memory");
    return 8;
}
