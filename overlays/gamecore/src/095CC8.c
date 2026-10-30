/* GAMECORE.XFF @ 0x095CC8 (48 B) - SCRSimpleExecCharaGeometry
 * Evidence: `lui/addiu` of <.data>+0x16A4 cached in $s0, `sw $a0 -> [$s0]` in
 * the delay slot of `jal <.text>+0x96130`, then `sw $zero -> [$s0]`.
 * UNCONFIRMED: callee func_00096130 (unnamed static)
 
 */
extern int D_kernel_data_16A4;
void func_00096130(void);

void SCRSimpleExecCharaGeometry(int value) {
    D_kernel_data_16A4 = value;
    func_00096130();
    D_kernel_data_16A4 = 0;
}
