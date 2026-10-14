/* asm/cod/010910.s -> func_00110910 @ 0x00110910 (0x84 bytes, 33 insns)
 *
 * Sorted insertion of `n` into a singly-linked list. The head is the 32-bit
 * pointer at D_00133918+0x18; each node has next (0x00), prev (0x04) and three
 * 64-bit words (0x10/0x18/0x20) — the original loads the node words with `ld`
 * and compares with `sltu`, so the sort key is an unsigned 64-bit expression
 * `f20 + f10 - f18`.
 *
 * Shape of the original (branch-likely delay slots only execute on the taken
 * edge):
 *   a2 = n; a4 = prev = 0; a3 = n->f20 + n->f10 - n->f18; a1 = cur = head;
 *   b .L44 (delay: a3 = key)
 * .L40: a1 = prev->next                ; cur = prev->next
 * .L44:
 *   beql a1, 0, .L70 (delay: n->f04 = prev)   ; n->prev = prev on both exits
 *   if (a3 >= cur->f20 + cur->f10 - cur->f18) { prev = cur; goto .L40 }
 *   n->f04 = prev
 * .L70:
 *   beqz a1, .L7C (delay: n->f00 = a1)  ; n->next = cur
 *   cur->f04 = n
 * .L7C:
 *   beqz a4, .L8C (delay: v0 = &D_00133918)
 *   jr ra (delay: prev->f00 = n)
 * .L8C:
 *   jr ra (delay: D_00133918.head = n)
 *
 * MATCHED (Session 6): byte-exact with the 2.9-ee-991111-01 revision (cc=29).
 * Session 4 had recorded this as a register-allocation failure under
 * ee-gcc2.96 (`n=$7, cur=$6, key=$5` vs the original's `n=$6, cur=$5, key=$7`);
 * the 2.9 revision reproduces the original assignment exactly, so the whole
 * `Register allocation` family has to be re-checked per revision. It was the
 * ≥30-instruction candidate for the -O sweep (docs/compiler.md §2.2).
 */
#include "symbols.h"

struct N10910 {
    struct N10910 *next;            /* 0x00 */
    struct N10910 *prev;            /* 0x04 */
    unsigned int   f08;             /* 0x08 */
    unsigned int   f0C;             /* 0x0C */
    unsigned long long f10;         /* 0x10 */
    unsigned long long f18;         /* 0x18 */
    unsigned long long f20;         /* 0x20 */
};

struct H10910 {
    char pad[0x18];
    struct N10910 *head;            /* 0x18 */
};

extern struct H10910 D_00133918;

void func_00110910(struct N10910 *n) {
    struct N10910 *prev = 0;
    unsigned long long key = n->f20 + n->f10 - n->f18;
    struct N10910 *cur = D_00133918.head;

    while (cur) {
        unsigned long long ck = cur->f20 + cur->f10 - cur->f18;
        if (key < ck)
            break;
        prev = cur;
        cur = prev->next;
    }

    n->prev = prev;
    n->next = cur;
    if (cur)
        cur->prev = n;
    if (prev)
        prev->next = n;
    else
        D_00133918.head = n;
}
