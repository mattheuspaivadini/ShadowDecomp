/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 13 [cc=29, default].
 * arena step (0130F0 twin, tag 0x70000000).
 * The original .s stays in the build (asm/cod/013148.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/013148.s -> func_00113148 @ 0x00113148 (0x58 bytes, 22 insns)
 *
 * Identical to func_001130F0 (see 0130F0.c for the full derivation: arena step
 * func_00113098, then a new 2-word packet with q[0] = tag | tagbits,
 * p->field08 = r, p->field0C = 0, p->field00 = q + 2 and q + 2 returned) except
 * for the tag bits: 0x70000000 instead of 0x10000000, which is why the constant
 * materialises with `lui` alone.
 * MATCH GUESS: cc=29
 */
struct S013148 {
    int *field00;                   /* 0x00 write cursor */
    int  field04;                   /* 0x04 */
    int *field08;                   /* 0x08 block start */
    int *field0C;                   /* 0x0C block to credit */
};

int *func_00113098(struct S013148 *p);

int func_00113148(struct S013148 *p, int tag) {
    int *q;
    int *r;
    int *next;

    r = func_00113098(p);
    q = p->field00;
    p->field08 = r;
    q[0] = tag | 0x70000000;
    p->field0C = 0;
    q[1] = 0;
    next = q + 2;
    p->field00 = next;
    return next;
}
