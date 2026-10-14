/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 7 [cc=29, default].
 * free-list pop; block layout differs.
 * The original .s stays in the build (asm/cod/009E50.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/009E50.s -> func_00109E50 @ 0x00109E50 (0x58 bytes, 22 insns)
 *
 * Free-list allocate inside the func_0010FB20/func_0010FB70 guard pair:
 *
 *   func_0010FB20();
 *   n = a0[3];                    (free-list head, next pointer at node +0x3C)
 *   if (n != 0) { a0[1] = 1; a0[3] = n->next; }
 *   else a0[1] = 0;
 *   func_0010FB70();
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

int func_0010FB20(void);
int func_0010FB70(void);

int func_00109E50(int *a0) {
    int n;

    func_0010FB20();
    n = a0[3];
    if (n != 0) {
        a0[1] = 1;
        a0[3] = ((struct N09E50 *)n)->next;
    } else {
        a0[1] = 0;
    }
    func_0010FB70();
    return n;
}
