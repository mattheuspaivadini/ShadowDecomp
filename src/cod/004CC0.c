/* asm/cod/004CC0.s -> padSysTickProc.
 * Source order with the p-killing store last in each reset block: sched1's register-weight tie-break hoists the store carrying REG_DEAD(p), so analog[0] (0x106) must be written last for [109,108,107] to stay at the block tails and be cross-jumped (Session 26).
 * MATCHED. */
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
                    p->analog[3] = 0x7F;
                    p->analog[2] = 0x7F;
                    p->analog[1] = 0x7F;
                    p->analog[0] = 0x7F;
                }
                break;
            }
        } else {
            p->phase = 0;
            p->btn[1] = 0;
            p->btn[0] = 0;
            p->analog[3] = 0x7F;
            p->analog[2] = 0x7F;
            p->analog[1] = 0x7F;
            p->analog[0] = 0x7F;
        }
    }
}
