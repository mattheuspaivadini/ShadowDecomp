/* STATUS (Session 6, step 3): NON_MATCHING - wave-2 draft [cc=296].
 * 011AF0/026110/0261A8 compile 8 bytes instead of 36/48 (incomplete);
 * 02D9C0 fails to compile. Kept for Session 7. */
 * Tail-call trampoline (without a frame;
 * cc=29 emits the bare j). */
void func_00111AF0(int a0) {
    func_001283D0(a0, 0);
}
