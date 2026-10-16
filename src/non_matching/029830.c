/* STATUS (Session 6, step 3): NON_MATCHING. The original uses bnez + b + nop (the p[2]!=0 path out of line); ee-gcc emits beqzl with the store in the delay slot (4 bytes short at cc=296/cc=29).
 * See docs/non-matching-backlog.md. */
/* asm/cod/029830.s -> func_00129830 @ 0x00129830
 * If the third word of the block is set, run func_0012E018 and clear words
 * 1 and 2; otherwise just clear word 1 and return 0. */
int __sfvwrite(void);

int func_00129830(int a0, int *p) {
    int r;

    if (p[2] != 0) {
        r = __sfvwrite();
        p[1] = 0;
        p[2] = 0;
        return r;
    }
    p[1] = 0;
    return 0;
}
