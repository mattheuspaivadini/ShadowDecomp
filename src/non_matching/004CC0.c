/* STATUS (Session 23, 2026-10-18): NON_MATCHING. best score 3 [cc=296] (was 34).
 * Typed 0x140-byte pad records, switch on the init phase, case-0 store order from a full 7! permutation. Residual = the analog-reset tail is not cross-jumped as [109,108,107] between case 1 and the not-ready branch (5040 else orders, 72 case-1 orders, goto/inline-helper sharing: no gain).
 * The original .s stays in the build (asm/cod/004CC0.s); this C
 * draft (Session 23) is kept for the record. */
struct PadSys {
    char pad000[0x100];
    unsigned char prof[4];      /* 0x100 button profile */
    unsigned char btn[2];       /* 0x104 */
    unsigned char analog[4];    /* 0x106 */
    char pad10A[0x0E];
    int state;                  /* 0x118 */
    int port;                   /* 0x11C */
    int phase;                  /* 0x120 */
    char pad124[0x1C];
};
extern struct PadSys D_0013D840[2];
int scePad2GetState(int port);
int scePad2GetButtonProfile(int port, unsigned char *prof);
int scePad2Read(int port, unsigned char *data);

void padSysTickProc(void) {
    struct PadSys *p;
    int i;

    for (i = 0; i < 2; i++) {
        p = &D_0013D840[i];
        if ((p->state = scePad2GetState(p->port)) == 1) {
            switch (p->phase) {
            case 0:
                scePad2GetButtonProfile(p->port, p->prof);
                p->btn[1] = 0;
                p->btn[0] = 0;
                p->analog[3] = 0x7F;
                p->analog[2] = 0x7F;
                p->analog[1] = 0x7F;
                p->analog[0] = 0x7F;
                p->phase++;
                break;
            case 1:
                scePad2Read(p->port, p->btn);
                p->btn[0] = p->prof[0] & ~p->btn[0];
                p->btn[1] = p->prof[1] & ~p->btn[1];
                if (p->prof[2] == 0) {
                    p->analog[0] = 0x7F;
                    p->analog[3] = 0x7F;
                    p->analog[2] = 0x7F;
                    p->analog[1] = 0x7F;
                }
                break;
            }
        } else {
            p->analog[0] = 0x7F;
            p->phase = 0;
            p->btn[1] = 0;
            p->btn[0] = 0;
            p->analog[3] = 0x7F;
            p->analog[2] = 0x7F;
            p->analog[1] = 0x7F;
        }
    }
}
