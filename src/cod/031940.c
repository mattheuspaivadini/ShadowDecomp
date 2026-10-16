/* asm/cod/031940.s -> func_00131940 @ 0x00131940
 * Tail-call trampoline (without a frame;
 * cc=29 emits the bare j). */
void iSyncDCache(int a0, int a1) {
    _sceSDC(a0 & 0xFFFFFFC0, a1 & 0xFFFFFFC0);
}
