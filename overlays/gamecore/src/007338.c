/* GAMECORE.XFF @ 0x007338 (56 B) - DebugPrintf3D_InitContext
 * Evidence: `$a2 = 0`, `$a3 = 1`, `$f12 = 0x3F000000` (0.5f),
 * `$f13 = 0x3F400000` (0.75f), `$f14 = 0x3F800000` (1.0f) and
 * `$f15 = $f14`, then a sibling `j` to `iosInitKPrintfContext3D` with `$a0` and
 * `$a1` untouched.
 * UNCONFIRMED: the callee prototype and the argument meanings.
 
 */
void iosInitKPrintfContext3D(void *a, void *b, int c, int d, float e, float f,
                             float g, float h);

void DebugPrintf3D_InitContext(void *arg0, void *arg1) {
    iosInitKPrintfContext3D(arg0, arg1, 0, 1, 0.5f, 0.75f, 1.0f, 1.0f);
}
