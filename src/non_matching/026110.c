/* STATUS (Session 6, step 3): NON_MATCHING - wave-2 draft [cc=296].
 * 011AF0/026110/0261A8 compile 8 bytes instead of 36/48 (incomplete);
 * 02D9C0 fails to compile. Kept for Session 7. */
 * Tail-call trampoline (with a frame;
 * cc=296 keeps the frame). */
void func_00126110(void) {
    func_001260A8(0x18);
}
