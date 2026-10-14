/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 12 [cc=29, default].
 * publish active sub-record 0x7C.
 * The original .s stays in the build (asm/cod/015778.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/015778.s -> func_00115778 @ 0x00115778 (0x5C bytes, 23 insns)
 *
 * Publish the active sub-record's 0x7C field for record `index` into the word
 * at D_0014B598 + index*0x334 + 8, returning 1 only when it changed:
 *
 *   v = *(int *)(func_001156A8(index) + 0x7C);   ; jal delay: s0 = index
 *   if (v == 0) return 0;                        ; beqz, stride in its slot
 *   base = (int)D_0014B598;                      ; lui/addiu %lo
 *   rec  = (int *)(base + 8 + index * 0x334);    ; addiu +0x8, then *0x334
 *   if (*rec == v) return 0;
 *   *rec = v; return 1;                          ; bnel + store in its delay
 *
 * func_001156A8 returns one of the record's two +0x80-apart sub-records whose
 * 0x7C field is the one to track. The `+ 8` is a *runtime* addiu (two-step
 * address build, like the matched 015008.c `base + 0x3340`): the offset must not
 * be folded into the %lo addend, so the base goes through an int local first
 * (the 0x334-stride table is *not* declared as an array of the record type
 * here, so the field offsets of 0151B8.c/015650.c do not apply).
 * 3-operand `mult` for the 0x334 stride + the 16-byte-spaced $s0/$ra frame => cc=29.
 * MATCH GUESS: cc=29 */
extern int D_0014B598[];   /* .bss 0x0014B598: 16 records of 0x334 bytes */
int func_001156A8(int index);

int func_00115778(int index) {
    int base;
    int *rec;
    int v;

    v = *(int *)(func_001156A8(index) + 0x7C);
    if (v == 0)
        return 0;
    base = (int)D_0014B598;
    rec = (int *)(base + 8 + index * 0x334);
    if (v != *rec) {
        *rec = v;
        return 1;
    }
    return 0;
}
