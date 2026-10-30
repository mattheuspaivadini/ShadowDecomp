/* GAMECORE.XFF @ 0x07D2B8 (44 B) - SetPlayerDangerEdgePoint
 * Evidence: `$a0` is saved in `$s0` across `jal GetSCRCharaAIWorkPtr`, then
 * `$a0 = $s0`, `$a1 = $v0 + 0x1BB0` and a sibling `j` to
 * `player_setDangerEdgePoint`.
 * UNCONFIRMED: the AI work field meaning and the callee prototype.
 
 */
void *GetSCRCharaAIWorkPtr(void);
void player_setDangerEdgePoint(void *arg, void *work);

void SetPlayerDangerEdgePoint(void *arg) {
    player_setDangerEdgePoint(arg, (char *)GetSCRCharaAIWorkPtr() + 0x1BB0);
}
