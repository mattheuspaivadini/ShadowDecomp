/* asm/cod/02E530.s -> func_0012E530 @ 0x0012E530
 * Tail-call trampoline (with a frame;
 * cc=296 keeps the frame). */
int _impure_ptr[];

void setlocale(int a0, int a1) {
    _setlocale_r(_impure_ptr[0], a0, a1);
}
