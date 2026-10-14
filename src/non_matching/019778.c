/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 6 [cc=29, default].
 * get_interface_id body.
 * The original .s stays in the build (asm/cod/019778.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/019778.s -> get_interface_id @ 0x00119778 (0x8C bytes, 35 insns)
 * Three-stage id fetch: a2 == 0 -> -0x21C (the producer slot was not
 * initialised); func_00119568(a0, a1, a2) (the "get" path) succeeding (>= 0)
 * -> 0; otherwise func_00119528(a0, a1, a2, a3) (the "wait" path, 019528.c
 * forwards 0x21 into func_00119498) whose negative result is returned, else 0
 * (the `bltz` after the second call and the `bgez` after the first share the
 * epilogue; the 0 is materialised in the first `bgez`'s delay slot).
 * MATCH GUESS: cc=29 (01919528/019498 family; filled jal shadows) */
int func_00119568(int a0, int a1, int a2);
int func_00119528(int a0, int a1, int a2, int a3);

int get_interface_id(int a0, int a1, int a2, int a3) {
    int r;

    if (a2 == 0)
        return -0x21C;
    if (func_00119568(a0, a1, a2) >= 0)
        return 0;
    r = func_00119528(a0, a1, a2, a3);
    if (r < 0)
        return r;
    return 0;
}
