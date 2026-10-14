/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 4 [cc=296, default].
 * setNewIopIdentifier-style report + index.
 * The original .s stays in the build (asm/cod/003340.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/003340.s -> setNewIopIdentifier @ 0x00103340 (0x70 bytes, 28 insns)
 *
 * Store the next 16-byte module-identifier record (named from the evidence of
 * the LoaderSys cluster; the string D_00136980 is this routine's own report):
 *
 *   func_00102CF8(D_00136980, module, D_0013A008);   ; report (index, module)
 *   idx = D_0013A008++;                             ; post-increment
 *   return func_001293B8(D_0013CB90 + idx * 16, module,
 *                        func_001290C4(module));
 *
 * `sll $s0,$v0,4` scales the *old* index and `addiu $v0,$v0,1` + the `sw` in
 * the `jal func_001290C4` delay slot is the post-increment; the record address
 * is `lui/addiu`-based (D_0013CB90 is a 0x400-byte .bss array, non-small) and
 * D_0013A008 is a gp-relative .sdata scalar, so its address is materialised
 * with `addiu $v1,$gp,%gp_rel(...)` for the increment store.  The last call is
 * a framed `j func_001293B8` (the 296 sibling-call shape).
 * MATCH GUESS: cc=296 */
extern int D_0013A008;          /* .sdata scalar: gp-relative */
extern char D_00136980[];       /* .rodata message: lui/%lo */
extern char D_0013CB90[];       /* .bss 0x400, 16-byte records: lui/%lo */

int func_00102CF8(char *fmt, ...);
int func_001290C4(char *s);
int func_001293B8(char *dst, char *src, int len);

int setNewIopIdentifier(char *module) {
    int idx;

    func_00102CF8(D_00136980, module, D_0013A008);
    idx = D_0013A008++;
    return func_001293B8(D_0013CB90 + idx * 16, module,
                         func_001290C4(module));
}
