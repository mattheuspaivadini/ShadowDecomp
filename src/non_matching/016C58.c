/* STATUS (Session 6, step 3): NON_MATCHING. The integer-only argument
 * save (no swc1 $f12..$f19) is not reproduced by a plain variadic
 * function - 10 instructions differ (the FP spill is present in ours).
 * See docs/non-matching-backlog.md. */
/* asm/cod/016C58.s -> func_00116C58 @ 0x00116C58
 * Saves $a1..$a7 into a 0x80 frame and returns (no FP spill). UNCONFIRMED
 * shape: the integer-only save area suggests the varargs variant that never
 * reads a floating-point argument. */
void func_00116C58(int a0, ...) {
}
