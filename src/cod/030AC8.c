/* asm/cod/030AC8.s -> func_00130AC8 @ 0x00130AC8
 * Tail-call trampoline (with a frame;
 * cc=296 keeps the frame). */
int _impure_ptr[];

void strtod(int a0, int a1) {
    _strtod_r(_impure_ptr[0], a0, a1);
}
