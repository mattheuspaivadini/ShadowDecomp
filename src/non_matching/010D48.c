/* STATUS (Session 36, 2026-10-20): NON_MATCHING. best score 2 [cc=ee-gcc2.9-991111-01-dtls13010 -g0 -fno-delayed-branch -G0] (was 9).
 * Levers that closed the gap 9 -> 2 (Session 36):
 *  - D_00133918.f0C must be volatile: the image reloads D.f0C after storing it
 *    (lw $v0,0xC($a3) at 0x10D98) and reloads n->f08 after storing it.
 *  - the n->next load must come from its own statement (nx = n->next) so it is
 *    emitted early (0x10D70); with `D.f14 = n->next` the load sinks below the
 *    n->f28 store (aliasing rule) and the n->next/n->f28 pair swaps instead.
 *  - the D.f10 increment is a separate statement (t10 = t10 + 1) placed before
 *    the volatile n->next load, so `fre` cannot sink it into the store.
 * Residual (1 instruction pair): the image has
 *    lw $v0,0x10($a3) / sll / lw $a0,0($a2) / addiu $v0,$v0,1 / sw $zero,0x28($a2) / sw $v0,0x10($a3)
 * i.e. the D.f10 increment (addiu) lands *between* the n->next load and the
 * n->f28 store; we emit it right after the n->f28 store. A sched1 tie between
 * the volatile n->f28 store and the addiu.
 * Negative results (Session 36): an exhaustive sweep of 1500 sources = 10
 * volatile models (node fields next/f08/f0C/f18/f28 and D fields f0C/f10/f14
 * volatile or not, pointer volatile or not) x every permutation of the
 * {D.f10 load, increment, n->next load, n->f28 store, D.f10 store} statements
 * (plus the single-statement `D.f10 = D.f10 + 1` form): the residual never
 * changes. 120 permutations of the local declaration order (the local-alloc
 * priority): all score 2. 2000 statement permutations of the best variant
 * (tools/permute_stmts.py): best 5. The counter forms `D.f10++`, `++D.f10`,
 * `D.f10 += 1`; the nx temp removed; the asm-volatile scheduling barrier
 * (changes the code size); 12 EE-GCC distributions (2.9-990721 ..
 * 2.9-991111a-dtls13010, 2.95.2/2.95.3, 2.96, 3.2) and the flag sets
 * -g0/-fno-delayed-branch/-G0/-fno-schedule-insns/-fno-schedule-insns2/
 * -fno-sched-interblock/-fno-strict-aliasing: the residual never changes.
 * Tooling note: build/s28/cobj.sh compiles through a fixed $W/s28/t.c path, so
 * parallel scoring with it races; build/s36/cobj_u.sh uses a unique work dir.
 * The original .s stays in the build (asm/cod/010D48.s); this C
 * draft (Session 36) is kept for the record. */
struct N10D48 {
    struct N10D48 *next;    /* 0x00 */
    int            f04;     /* 0x04 */
    int            f08;     /* 0x08 */
    int            f0C;     /* 0x0C */
    int            f10;     /* 0x10 */
    int            f14;     /* 0x14 */
    long long      f18;     /* 0x18 */
    int            f20;     /* 0x20 */
    int            f24;     /* 0x24 */
    int            f28;     /* 0x28 */
};

struct D10D48 {
    int             pad00;  /* 0x00 */
    int             pad04;  /* 0x04 */
    int             pad08;  /* 0x08 */
    volatile int    f0C;    /* 0x0C */
    int             f10;    /* 0x10 */
    struct N10D48  *f14;    /* 0x14 */
};

extern struct D10D48 D_00133918;

int iAllocTimerCounter(void) {
    volatile struct N10D48 *n;
    struct N10D48 *nx;
    unsigned int v;
    unsigned int t10;
    int t0c;

    n = D_00133918.f14;
    if (n == 0)
        return 0x80008005;
    v = (unsigned int)n << 4;
    t10 = D_00133918.f10;
    t10 = t10 + 1;
    nx = n->next;
    n->f28 = 0;
    D_00133918.f10 = t10;
    n->f0C = 0;
    D_00133918.f14 = nx;
    t0c = D_00133918.f0C;
    n->f18 = 0;
    D_00133918.f0C = t0c + 1;
    n->f08 = ((D_00133918.f0C << 1) & 0x3FE) | 1;
    return (int)(v | n->f08);
}
