/* GAMECORE.XFF @ 0x07D350 (44 B) - SetPlayerHellDangerPoint
 * Evidence: `$a0` is saved in `$s0` across `jal GetSCRCharaAIWorkPtr`, then
 * `$a0 = $s0`, `$a1 = $v0 + 0x1BB0` and a sibling `j` to
 * `player_setHellDangerPoint`.
 * UNCONFIRMED: the AI work field meaning and the callee prototype.
 
 */
void *GetSCRCharaAIWorkPtr(void);
void player_setHellDangerPoint(void *arg, void *work);

void SetPlayerHellDangerPoint(void *arg) {
    player_setHellDangerPoint(arg, (char *)GetSCRCharaAIWorkPtr() + 0x1BB0);
}
