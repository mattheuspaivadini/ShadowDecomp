/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 34 [cc=296].
 * R2 w45a_1: block-layout (off += 0x140 induction)
 * The original .s stays in the build (asm/cod/004CC0.s); this C
 * draft (Session 8) is kept for the record. */
extern char D_0013D840[];   /* lui/%lo, 0x140-byte records */

int scePad2GetState(int a0);
int scePad2GetButtonProfile(int a0, void *a1);
int scePad2Read(int a0, void *a1);

void padSysTickProc(void) {
    char *p;
    char *q;
    int i;
    int off;
    int st;
    int r;

    off = 0;
    p = D_0013D840 + off;
    for (i = 0; i < 2; i++) {
        off += 0x140;
        r = scePad2GetState(*(int *)(p + 0x11C));
        *(int *)(p + 0x118) = r;
        if (r == 1) {
            st = *(int *)(p + 0x120);
            if (st == 0) {
                scePad2GetButtonProfile(*(int *)(p + 0x11C), p + 0x100);
                *(char *)(p + 0x105) = 0;
                *(char *)(p + 0x104) = 0;
                *(char *)(p + 0x109) = 0x7F;
                *(int *)(p + 0x120) = *(int *)(p + 0x120) + 1;
                *(char *)(p + 0x108) = 0x7F;
                *(char *)(p + 0x107) = 0x7F;
                *(char *)(p + 0x106) = 0x7F;
            } else if (st == 1) {
                q = p + 0x104;
                scePad2Read(*(int *)(p + 0x11C), q);
                *(unsigned char *)q =
                    *(unsigned char *)(p + 0x100) & ~*(unsigned char *)q;
                *(unsigned char *)(p + 0x105) =
                    *(unsigned char *)(p + 0x101) &
                    ~*(unsigned char *)(p + 0x105);
                if (*(unsigned char *)(p + 0x102) == 0) {
                    *(char *)(p + 0x106) = 0x7F;
                    *(char *)(p + 0x109) = 0x7F;
                    *(char *)(p + 0x108) = 0x7F;
                    *(char *)(p + 0x107) = 0x7F;
                }
            }
        } else {
            *(char *)(p + 0x106) = 0x7F;
            *(int *)(p + 0x120) = 0;
            *(char *)(p + 0x105) = 0;
            *(char *)(p + 0x104) = 0;
            *(char *)(p + 0x109) = 0x7F;
            *(char *)(p + 0x108) = 0x7F;
            *(char *)(p + 0x107) = 0x7F;
        }
        p = D_0013D840 + off;
    }
}
