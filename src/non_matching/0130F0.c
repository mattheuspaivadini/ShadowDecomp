/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 13 [cc=29, default].
 * arena step; field/store order differs.
 * The original .s stays in the build (asm/cod/0130F0.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/0130F0.s -> func_001130F0 @ 0x001130F0 (0x58 bytes, 22 insns)
 *
 * DMAC/GIF packet builder: close the current block with the arena step
 * func_00113098(p) (the same object as the archived 013098.c / matched
 * 0131F8.c: 0x00 = write cursor, 0x08 = current block, 0x0C = block to
 * credit), then open a new 2-word packet
 *
 *   q = p->field00;                 (0x00 write cursor)
 *   p->field08 = r;                 (r = func_00113098's return)
 *   q[0] = tag | 0x10000000;        (0x10000000 = PACKED-mode tag bits)
 *   p->field0C = 0;
 *   q[1] = 0;
 *   p->field00 = q + 2;             (also the return value in $v0)
 *
 * 013148 is the same routine with the 0x70000000 tag bits (A+D mode) - the
 * `or` constant is the only difference (`lui %hi(0x70000000)` alone, no `ori`).
 * Statement order follows the asm's store sequence (0x08, q[0], 0x0C, 0x00,
 * q[1]); `q[1] = 0` is the last store and the ambient `addiu $sp`/`ld` slots
 * around it are the scheduled epilogue.
 * MATCH GUESS: cc=29
 */
struct S0130F0 {
    int *field00;                   /* 0x00 write cursor */
    int  field04;                   /* 0x04 */
    int *field08;                   /* 0x08 block start */
    int *field0C;                   /* 0x0C block to credit */
};

int *func_00113098(struct S0130F0 *p);

int func_001130F0(struct S0130F0 *p, int tag) {
    int *q;
    int *r;
    int *next;

    r = func_00113098(p);
    q = p->field00;
    p->field08 = r;
    q[0] = tag | 0x10000000;
    p->field0C = 0;
    q[1] = 0;
    next = q + 2;
    p->field00 = next;
    return next;
}
