/* asm/cod/0288E8.s -> func_001288E8 @ 0x001288E8
 * Tail-call trampoline (with a frame;
 * cc=296 keeps the frame). */
int _impure_ptr[];

void raise(int a0) {
    _raise_r(_impure_ptr[0], a0);
}
