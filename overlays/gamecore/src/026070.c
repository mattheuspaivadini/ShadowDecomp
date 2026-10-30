/* GAMECORE.XFF @ 0x026070 (44 B) - StaffRollCancel
 * Evidence: `mtc1` of 0x40400000 (3.0f) into `$f12`, `$a0 = $a1 = 0`, a
 * `sw $zero` into .data+0xF9C and a sibling `j` to `fadeOut`.
 * UNCONFIRMED: the callee prototype and the .data field meaning.
 
 */
extern int D_kernel_data_0F9C[];
void fadeOut(int a, int b, float time);

void StaffRollCancel(void) {
    D_kernel_data_0F9C[0] = 0;
    fadeOut(0, 0, 3.0f);
}
