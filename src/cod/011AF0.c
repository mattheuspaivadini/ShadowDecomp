/* asm/cod/011AF0.s -> func_00111AF0 @ 0x00111AF0
 * Tail-call trampoline (without a frame;
 * cc=29 emits the bare j). */
void func_00111AF0(int a0) {
    func_001283D0(a0, 0);
}
