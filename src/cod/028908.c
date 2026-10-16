/* asm/cod/028908.s -> func_00128908 @ 0x00128908
 * Tail-call trampoline (with a frame;
 * cc=296 keeps the frame). */
int _impure_ptr[];

void signal(int a0, int a1) {
    _signal_r(_impure_ptr[0], a0, a1);
}
