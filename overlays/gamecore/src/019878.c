/* GAMECORE.XFF @ 0x019878 (36 B) - gStatStartTimeAttack
 * Evidence: `sw 2` into .data+0x948 and `$a0 = 1` before a sibling `j` to
 * `SetTimeAttackTimeFlag`.
 * UNCONFIRMED: the state field meaning (2 = running).
 
 */
extern int D_kernel_data_0948[];
void SetTimeAttackTimeFlag(int on);

void gStatStartTimeAttack(void) {
    D_kernel_data_0948[0] = 2;
    SetTimeAttackTimeFlag(1);
}
