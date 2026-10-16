/* STATUS (10, 2026-10-16): NON_MATCHING. best score 5 [cc=29].
 * 
 * The original .s stays in the build (asm/cod/011750.s); this C
 * draft (10) is kept for the record. */
/* asm/cod/011750.s -> func_00111750 @ 0x00111750 (0x5C bytes, 23 insns)
 *
 * Dispatch a0 (masked with 0xFE) into a node's handler; when the handler
 * declines (returns 0) the node is pushed onto the D_0014AC80 list and -1 is
 * returned, otherwise the handler's value is returned:
 *   r = node->fn(((a3 << 4) | (a0 & 0xFE)) | 1, a1, a2, node->field0C);
 *   if (r) return r;
 *   old = D_0014AC80[0];
 *   D_0014AC80[0] = node;
 *   node->next = old;
 *   node->field04 = 0;
 *   return -1;
 * a1/a2 are passed through untouched (their argument registers are not written)
 * and node->field0C (0xC) becomes the handler's 4th argument; the handler
 * address is loaded from node+8. The store order (global first, then node->next,
 * then node->field04) is reproduced with the `old` local.
 * The saves are 16 bytes apart ($s0 at 0x00, $ra at 0x10) - the cc=29 slot
 * layout (cc=296 would put $ra at 0x08 and make the frame 0x10).
 * MATCH GUESS: cc=29 */
struct S011750 {
    struct S011750 *next;                        /* 0x00 */
    int             field04;                     /* 0x04 */
    int (*fn)(int a0, int a1, int a2, int a3);   /* 0x08 */
    int             field0C;                     /* 0x0C */
};

extern struct S011750 *D_0014AC80[];   /* lui/%lo (non-small) */

int func_00111750(int a0, int a1, int a2, struct S011750 *node) {
    struct S011750 *old;
    int r;

    r = node->fn((int)(((unsigned int)node << 4) | (a0 & 0xFE)) | 1, a1, a2,
                 node->field0C);
    if (r != 0)
        return r;
    old = D_0014AC80[0];
    D_0014AC80[0] = node;
    node->next = old;
    node->field04 = 0;
    return -1;
}
