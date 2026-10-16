/* asm/cod/028930.s -> func_00128930 @ 0x00128930
 * Tail-call trampoline (with a frame;
 * cc=296 keeps the frame). */
int _impure_ptr[];

void _init_signal(void) {
    _init_signal_r(_impure_ptr[0]);
}
