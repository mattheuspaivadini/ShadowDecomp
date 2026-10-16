/* asm/cod/02FB90.s -> func_0012FB90 @ 0x0012FB90
 * Tail-call trampoline (with a frame;
 * cc=296 keeps the frame). */
void __sclose(char *p) {
    _close_r(*(int *)(p + 0x54), *(short *)(p + 0xE));
}
