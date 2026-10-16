/* asm/cod/02D9E0.s -> func_0012D9E0 @ 0x0012D9E0
 * Tail-call trampoline (with a frame;
 * cc=296 keeps the frame). */
int _impure_ptr[];

void _cleanup(void) {
    _cleanup_r(_impure_ptr[0]);
}
