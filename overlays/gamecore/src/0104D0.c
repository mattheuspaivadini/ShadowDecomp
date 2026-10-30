/* GAMECORE.XFF @ 0x0104D0 (32 B) - bossStatSetDeadBoss
 * Evidence: sw a0 -> .data+0x6E8; a0=[a0+0x18]; sibling j _gameFlagCls
 * UNCONFIRMED: types
 */
extern int D_kernel_data_06E8[];
void _gameFlagCls(int f);

void bossStatSetDeadBoss(int boss) {
    D_kernel_data_06E8[0] = boss;
    _gameFlagCls(*(int *)(boss + 0x18));
}
