/* GAMECORE.XFF @ 0x092E10 (40 B) - nico_player_colfit_GetUpper
 * Evidence: `$a0 -> $a1`, `$a2 = ZeroPoint`, `$a0 = .bss+0x7CD0`, sibling `j`
 * to `nico_IK_getAddSubPosition`.
 * UNCONFIRMED: the .bss buffer's meaning and the callee prototype.
 
 */
extern char D_kernel_bss_7CD0[];
extern char ZeroPoint[];
void nico_IK_getAddSubPosition(void *out, void *arg, void *zero);

void nico_player_colfit_GetUpper(void *arg) {
    nico_IK_getAddSubPosition(D_kernel_bss_7CD0, arg, ZeroPoint);
}
