/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 2 [cc=29, default, variant best_void].
 * same 2.9-frame + sibling-`j` conflict as 0230B0.
 * The original .s stays in the build (asm/cod/0101D8.s); this C
 * draft (Session 7) is kept for the record. */
/* v01: void prototypes for the wrapper and the tail callee. */
void func_00110118(int a0);
void func_00106C00(int a0);

void func_001101D8(int a0) {
    int saved = a0;

    func_00110118(a0);
    func_00106C00(saved);
}
