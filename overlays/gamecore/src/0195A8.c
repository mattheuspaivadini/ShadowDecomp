/* GAMECORE.XFF @ 0x0195A8 (48 B) - gStatOmakeSave
 * Evidence: five zero arguments in `$a0`..`$a3`/`$t0`, `$t1 = .bss+0x49B0` and
 * a sibling `j` to `gameFlagCheckPointSave` (six integer arguments, EE ABI
 * passes the 5th/6th in `$t0`/`$t1`).
 * UNCONFIRMED: the flag block meaning and the callee prototype.
 
 */
extern unsigned char D_kernel_bss_49B0[];
void gameFlagCheckPointSave(int a, int b, int c, int d, int e, void *flags);

void gStatOmakeSave(void) {
    gameFlagCheckPointSave(0, 0, 0, 0, 0, D_kernel_bss_49B0);
}
