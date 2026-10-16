/* asm/cod/0030C8.s -> func_001030C8 @ 0x001030C8
 * Tail-call trampoline to sceStdioMkdir (frame + `j`, the cc=296 shape).
 * The parameter count follows the ps2sdk prototype (UNCONFIRMED for
 * this build); the code is a pure pass-through, so the count does not
 * change the emitted bytes. */
int sceMkdir(int a0, int a1);

int LoaderSysMkdir(int a0, int a1) {
    return sceMkdir(a0, a1);
}
