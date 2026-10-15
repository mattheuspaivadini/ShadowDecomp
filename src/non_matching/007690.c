/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 12 [cc=29].
 * R2 w45a_1: reg-alloc (two parallel byte pointers, 3-case tree)
 * The original .s stays in the build (asm/cod/007690.s); this C
 * draft (Session 8) is kept for the record. */
extern int  D_00143C90[];   /* lui/%lo (thread handle) */
extern char D_00137C88[];   /* "## internel error in libkernl.a!\n" */

int  func_00107020(int a0);
int  func_00106F10(unsigned char c);
int  func_00106E90(unsigned char c);
int  func_00106F50(unsigned char c);
int  func_00108F78(char *msg);

void func_00107690(char *a0) {
    unsigned char *t;
    unsigned char *u;
    int n;
    unsigned char c;

    t = (unsigned char *)(a0 + 8);
    u = (unsigned char *)(a0 + 9);
    for (;;) {
        func_00107020(D_00143C90[0]);
        n = *(int *)a0 & 0x1FF;
        *(int *)a0 = n + 1;
        c = t[n * 2];
        switch (c) {
        case 0:
            func_00106F10(u[n * 2]);
            break;
        case 1:
            func_00106E90(u[n * 2]);
            break;
        case 2:
            func_00106F50(u[n * 2]);
            break;
        default:
            func_00108F78(D_00137C88);
            break;
        }
    }
}
