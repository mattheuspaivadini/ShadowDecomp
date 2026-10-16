/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 12 [cc=29].
 * R2 w45a_1: reg-alloc (two parallel byte pointers, 3-case tree)
 * The original .s stays in the build (asm/cod/007690.s); this C
 * draft (Session 8) is kept for the record. */
extern int  D_00143C90[];   /* lui/%lo (thread handle) */
extern char D_00137C88[];   /* "## internel error in libkernl.a!\n" */

int  WaitSema(int a0);
int  WakeupThread(unsigned char c);
int  RotateThreadReadyQueue(unsigned char c);
int  SuspendThread(unsigned char c);
int  kprintf(char *msg);

void func_00107690(char *a0) {
    unsigned char *t;
    unsigned char *u;
    int n;
    unsigned char c;

    t = (unsigned char *)(a0 + 8);
    u = (unsigned char *)(a0 + 9);
    for (;;) {
        WaitSema(D_00143C90[0]);
        n = *(int *)a0 & 0x1FF;
        *(int *)a0 = n + 1;
        c = t[n * 2];
        switch (c) {
        case 0:
            WakeupThread(u[n * 2]);
            break;
        case 1:
            RotateThreadReadyQueue(u[n * 2]);
            break;
        case 2:
            SuspendThread(u[n * 2]);
            break;
        default:
            kprintf(D_00137C88);
            break;
        }
    }
}
