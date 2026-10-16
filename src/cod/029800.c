/* asm/cod/029800.s -> func_00129800 @ 0x00129800
 * Tail-call trampoline (with a frame;
 * cc=296 keeps the frame). */
int _impure_ptr[];

void strtol(int a0, int a1, int a2) {
    _strtol_r(_impure_ptr[0], a0, a1, a2);
}
