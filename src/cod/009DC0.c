/* asm/cod/009DC0.s -> if.
 * SCE sifrpc queue unlink; same loop shape as sceSifRemoveRpc (Session 19)
 * MATCHED. */
/* asm/cod/009DC0.s -> sceSifRemoveRpcQueue @ 0x00109DC0 (0x90 bytes, 36 insns)
 *
 * Unlink a node from the singly-linked list headed at D_00145940+0x28 (node
 * forward link at +0x14), inside the DIntr/EIntr guard pair.
 * The release is unconditional (the guard's result is not tested); the value
 * returned is the node whose link was rewired - the removed head itself, or
 * the predecessor of the removed node, or 0 when the node is not in the list:
 *
 *   DIntr();
 *   p = D_00145940.head;
 *   if (p == target) { D_00145940.head = p->next; }
 *   else { while (p != 0 && p->next != target) p = p->next;
 *          if (p != 0) p->next = target->next; }
 *   EIntr();
 *   return p;                      ; daddu $v0,$s0 (kept in $s0 across calls)
 *
 * The peeled first `p->next` test and the `bnel`/`beql` delay-slot loads match
 * the rotated `while` above; $s1 holds the target across both calls.
 * UNCONFIRMED: node/list field names.
 * MATCH GUESS: cc=29 (the DIntr wrapper family and the 0x00109xxx
 * block are 2.9 TUs) */
struct N09DC0 {
    char          pad00[0x14];
    struct N09DC0 *next;    /* 0x14 */
};

struct L09DC0 {
    char           pad00[0x28];
    struct N09DC0 *head;    /* 0x28 */
};

extern struct L09DC0 D_00145940;   /* .bss/.data, outside small-data -> lui/%lo */

int DIntr(void);
int EIntr(void);

struct N09DC0 *sceSifRemoveRpcQueue(struct N09DC0 *target) {
    struct N09DC0 *p;

    DIntr();
    p = D_00145940.head;
    if (p == target) {
        D_00145940.head = p->next;
    } else if (p != 0) {
        while (p->next != target) {
            p = p->next;
            if (p == 0)
                goto out;
        }
        p->next = target->next;
    }
out:
    EIntr();
    return p;
}
