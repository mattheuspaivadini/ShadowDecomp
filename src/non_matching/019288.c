/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 44 [cc=296 -g0].
 * session9 R2 waveA; residual class not auto-classified
 * The original .s stays in the build (asm/cod/019288.s); this C
 * draft (Session 9) is kept for the record. */
struct C019288 {
    char pad00[0x24];
    int  f24;       /* 0x24 busy/done word */
};

int SceMrpcBind(int a0, int a1, int a2, int a3, int a4, int a5);

int func_00119288(int a0, int a1, int a2, int a3) {
    struct C019288 *c;
    unsigned int i;

    c = (struct C019288 *)a0;
    if (a1 < 0x100 || (a1 & 0x3F) != 0)
        return -0x21F;
    if (SceMrpcBind(a0, 0x80001201, 0, a1, a2, a3) < 0)
        return -0x21C;
    if (c->f24 == 0) {
        i = 0xFFFF0000;
        for (;;) {
            i = i + 0xFFFF;
            if (i == 0xFFFFFFFF)
                break;
        }
        return i;
    }
    return 0;
}
