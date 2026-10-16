/* asm/cod/031A80.s -> func_00131A80 @ 0x00131A80
 * Tail-call trampoline (without a frame;
 * cc=29 emits the bare j). */
void iInvalidDCache(int a0, int a1) {
    _sceIDC(a0 & 0xFFFFFFC0, a1 & 0xFFFFFFC0);
}
