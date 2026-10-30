/* GAMECORE.XFF @ 0x04E1B0 (48 B) - createBossBloodParamMenu
 * Evidence: `lui`/`addiu` build `.data+0x12C0`, `lw $v0,0x30` is tested and
 * skipped when set; otherwise `$a1 = 0` and a sibling `j` to `createParamMenu`
 * with `$a0` still the same address.
 * UNCONFIRMED: the menu struct field meaning and the callee prototype.
 
 */
struct BossBloodParamMenu {
    char pad[0x30];
    int created;
};
extern struct BossBloodParamMenu D_kernel_data_12C0;
void createParamMenu(void *menu, int arg);

void createBossBloodParamMenu(void) {
    if (D_kernel_data_12C0.created == 0)
        createParamMenu(&D_kernel_data_12C0, 0);
}
