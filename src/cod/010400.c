/* asm/cod/010400.s -> func_00110400 @ 0x00110400
 * Tail-call trampoline (without a frame;
 * cc=29 emits the bare j). */
void func_00110400(int a0) {
    func_00110390(0xB0001000, a0);
}
