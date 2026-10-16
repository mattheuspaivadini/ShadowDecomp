/* asm/cod/010400.s -> func_00110400 @ 0x00110400
 * Tail-call trampoline (without a frame;
 * cc=29 emits the bare j). */
void SetT2_COUNT(int a0) {
    SetT2(0xB0001000, a0);
}
