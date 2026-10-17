/* asm/cod/009E50.s -> if.
 * SCE sifrpc free-list pop; empty arm first, next loaded before the stores (Session 19)
 * MATCHED. */
/* asm/cod/009E50.s -> sceSifGetNextRequest @ 0x00109E50 (0x58 bytes, 22 insns)
 *
 * Free-list allocate inside the DIntr/EIntr guard pair:
 *
 *   DIntr();
 *   n = a0[3];                    (free-list head, next pointer at node +0x3C)
 *   if (n != 0) { a0[1] = 1; a0[3] = n->next; }
 *   else a0[1] = 0;
 *   EIntr();
 *   return n;                     (the popped node, or 0)
 *
 * The old head must survive the second call, hence `$s1`/`$s0` saves and the
 * single trailing return (the family pattern of the matched 010EA0/011168: the
 * value is returned, the guard result is only used for the unlock there - here
 * the unlock is unconditional). The taken path loads node+0x3C in the `bnel`
 * delay slot, so that load must live only in the taken branch.
 * MATCH GUESS: cc=29
 */
struct N09E50 {
    char pad[0x3C];
    int next;                       /* 0x3C */
};

int DIntr(void);
int EIntr(void);

int sceSifGetNextRequest(int *a0) {
    int n;

    DIntr();
    n = a0[3];
    if (n == 0) {
        a0[1] = 0;
    } else {
        int next = ((struct N09E50 *)n)->next;
        a0[1] = 1;
        a0[3] = next;
    }
    EIntr();
    return n;
}
