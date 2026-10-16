/* asm/cod/028950.s -> func_00128950 @ 0x00128950
 * Tail-call trampoline (with a frame;
 * cc=296 keeps the frame). */
int _impure_ptr[];

void __sigtramp(int a0) {
    __sigtramp_r(_impure_ptr[0], a0);
}
