/* asm/cod/010410.s -> func_00110410 @ 0x00110410
 * Tail-call trampoline (without a frame;
 * cc=29 emits the bare j). */
void func_00110410(int a0) {
    func_00110390(0xB0001010, a0);
}
