/* STATUS (10, 2026-10-16): NON_MATCHING. best score 6 [cc=296].
 * 
 * The original .s stays in the build (asm/cod/0262F8.s); this C
 * draft (10) is kept for the record. */
/* asm/cod/0262F8.s -> func_001262F8 @ 0x001262F8 (0x8C bytes, 35 insns)
 * Walk an offset-linked block list starting at p and account for every block:
 *   p[0] is the offset to the next block (the next header is p + p[0] + 4, so
 *   the advance is `addu $v0,$a0,$a6` then `addiu $a0,$v0,4` and the loop test
 *   reloads the new block's p[0] into $a6);
 *   a block with p[1] == 0 is skipped straight to the advance (the `beql` puts
 *   the advance's `addu` in its delay slot);
 *   a block with p[2] != 0 pushes itself into the caller's list (list[0] = the
 *   array base, list[1] = the count: `lw` base, `lw` count, `sll`, `addiu`
 *   count+1, `sw` count, `sw` block) and updates the accumulators:
 *   min = min(min, p[2]) (sltu + movn) and
 *   max = max(max, p[2] + p[3]) (addu + sltu + movn);
 *   finally *pmin = min, *pmax = max.
 * The p[2] compare/movn is computed before the push block (in the `beqz p[2]`
 * delay slot) and p[0]/p[3] are re-loaded after the push store (potential
 * aliasing).
 * MATCH GUESS: cc=296 (0x1262xx: 026298.c/0262B8.c) */
void func_001262F8(int *p, int *list, unsigned int *pmin, unsigned int *pmax) {
    unsigned int min = *pmin;
    unsigned int max = *pmax;

    while (p[0] != 0) {
        if (p[1] != 0) {
            unsigned int sz = (unsigned int)p[2];

            if (sz != 0) {
                int *base;
                unsigned int acc;
                int k;

                base = (int *)list[0];
                if (base != 0) {
                    k = list[1];
                    list[1] = k + 1;
                    base[k] = (int)p;
                }
                if (sz < min)
                    min = sz;
                acc = sz + (unsigned int)p[3];
                if (max < acc)
                    max = acc;
            }
        }
        p = (int *)((char *)p + p[0] + 4);
    }
    *pmin = min;
    *pmax = max;
}
