/* STATUS (Session 5, step 2): NON_MATCHING - best attempt [cc=296] is not byte-exact.
 * 22 instructions: pipelined table scan (same family as 002790/0027E0/002830/002970).
 * See docs/progress.md for the family classification. */
/* func_00102730 @ 0x00102730 (0x5C bytes): find the first pair with a
 * negative first word in D_0013BF90[], store (b, a) there; full table walks
 * to index -1. */
struct P002730 {
    int a;   /* 0x0 */
    int b;   /* 0x4 */
};

extern struct P002730 D_0013BF90[];

void func_00102730(int a, int b) {
    int i;

    for (i = 0; i < 256; i++) {
        if (D_0013BF90[i].a < 0)
            break;
    }
    if (i == 256)
        i = -1;
    D_0013BF90[i].b = a;
    D_0013BF90[i].a = b;
}
