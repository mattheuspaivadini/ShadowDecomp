/* asm/cod/010420.s -> func_00110420 @ 0x00110420
 * Tail-call trampoline (without a frame;
 * cc=29 emits the bare j). */
void SetT2_COMP(int a0) {
    SetT2(0xB0001020, a0);
}
