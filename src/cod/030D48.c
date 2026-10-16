/* asm/cod/030D48.s -> func_00130D48 @ 0x00130D48
 * Tail-call trampoline (with a frame;
 * cc=296 keeps the frame). */
int _impure_ptr[];

void strtoul(int a0, int a1, int a2) {
    _strtoul_r(_impure_ptr[0], a0, a1, a2);
}
