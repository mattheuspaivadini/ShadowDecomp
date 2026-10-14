/* asm/cod/010420.s -> func_00110420 @ 0x00110420
 * Tail-call trampoline (without a frame;
 * cc=29 emits the bare j). */
void func_00110420(int a0) {
    func_00110390(0xB0001020, a0);
}
