/* asm/cod/031940.s -> func_00131940 @ 0x00131940
 * Tail-call trampoline (without a frame;
 * cc=29 emits the bare j). */
void func_00131940(int a0, int a1) {
    func_00131818(a0 & 0xFFFFFFC0, a1 & 0xFFFFFFC0);
}
