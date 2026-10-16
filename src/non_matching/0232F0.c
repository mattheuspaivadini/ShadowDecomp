/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 25 [cc=29, default].
 * D_00135960 dispatch.
 * The original .s stays in the build (asm/cod/0232F0.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/0232F0.s -> func_001232F0 @ 0x001232F0 (0x8C bytes, 35 insns)
 * Release/shutdown dispatcher for the D_00135960 handle:
 *   r is 1 (its value is materialised at the top and doubles as the `a0 == 1`
 *   comparand: `beq $a0,$s0` with $s0 = 1, then `bgez`, then `$s0 = 0` before
 *   the two success returns);
 *   D_00135960 < 0            -> -1
 *   a0 == 0                   -> func_00107020(D_00135960); func_00123208();
 *                                r = 0; return r
 *   a0 == r (1)               -> func_00107030(D_00135960) == -1 ? return r
 *                                : func_00123208(); r = 0; return r
 *   otherwise                 -> -0x65
 * The three `daddu $v0,$s0,$zero` sites are three separate `return r;`
 * statements (the -1 and both success returns share the .L0012336C epilogue
 * entry, -0x65 has its own at .L00123370).
 * MATCH GUESS: cc=29 (D_00135960 accessor family: 0231A8/023208) */
void WaitSema(int a0);
int PollSema(int a0);
int func_00123208(void);

extern int D_00135960[];   /* .data 0x00135960, 4 bytes - array => lui/%lo */

int sce_sync(int a0) {
    int r;

    r = 1;
    if (D_00135960[0] < 0)
        return -1;
    if (a0 == 0) {
        WaitSema(D_00135960[0]);
        func_00123208();
        r = 0;
        return r;
    }
    if (a0 == r) {
        if (PollSema(D_00135960[0]) == -1)
            return r;
        func_00123208();
        r = 0;
        return r;
    }
    return -0x65;
}
