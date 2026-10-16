/* asm/cod/0030E0.s -> func_001030E0 @ 0x001030E0
 * Tail-call trampoline to sceStdioGetstat (frame + `j`, the cc=296 shape).
 * The parameter count follows the ps2sdk prototype (UNCONFIRMED for
 * this build); the code is a pure pass-through, so the count does not
 * change the emitted bytes. */
int sceGetstat(int a0, int a1);

int LoaderSysGetstat(int a0, int a1) {
    return sceGetstat(a0, a1);
}
