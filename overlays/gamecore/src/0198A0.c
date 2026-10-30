/* GAMECORE.XFF @ 0x0198A0 (36 B) - gStatStopTimeAttack
 * Evidence: `sw 3` into .data+0x948 and `$a0 = 0` before a sibling `j` to
 * `SetTimeAttackTimeFlag`.
 * UNCONFIRMED: the state field meaning (3 = stopped).
 
 */
extern int D_kernel_data_0948[];
void SetTimeAttackTimeFlag(int on);

void gStatStopTimeAttack(void) {
    D_kernel_data_0948[0] = 3;
    SetTimeAttackTimeFlag(0);
}
