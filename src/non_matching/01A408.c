/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 3 [cc=29, default].
 * guarded record + two error codes.
 * The original .s stays in the build (asm/cod/01A408.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/01A408.s -> func_0011A408 @ 0x0011A408 (0x90 bytes, 36 insns)
 * Guarded connection set-up, returning 0x8101xxxx status codes:
 *   D_00135630 == 0                       -> 0x81018001 (not initialised)
 *   (unsigned)(p[1] - 2) >= 2 (not 2/3)   -> 0x81010016
 *   p[2] != 0                             -> 0x81010016   (both errors share
 *                                            the merged return block)
 *   r = func_00121EF8(); r < 0            -> 0x81010017
 *   func_0011C198(r); return func_001220F8(r);
 * The range check is the `addiu -2` + `sltiu 2` + `beqz` fold; the final call
 * is a `jal` + real epilogue (no tail `j`), so no sibling-call folding.
 * MATCH GUESS: cc=29 (0x01C1xx / func_001220F8 error-code family) */
extern int D_00135630[];   /* .data 0x00135630, 4 bytes - array => lui/%lo */

int _sceMcCoreCreateSocket(void);
int _sceMcFatInit2(int index);
int _sceMcCoreChangeSocketTypeMc2Dbc(int i);

int sceMc2CreateSocket(int *p) {
    int r;

    if (D_00135630[0] == 0)
        return 0x81018001;
    if ((unsigned)(p[1] - 2) >= 2)
        return 0x81010016;
    if (p[2] != 0)
        return 0x81010016;
    r = _sceMcCoreCreateSocket();
    if (r < 0)
        return 0x81010017;
    _sceMcFatInit2(r);
    return _sceMcCoreChangeSocketTypeMc2Dbc(r);
}
