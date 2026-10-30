/* GAMECORE.XFF @ 0x07D2E8 (44 B) - SetPlayerDangerEdgeOtherSidePlanePoint
 * Evidence: `$a0` is saved in `$s0` across `jal GetSCRCharaAIWorkPtr`, then
 * `$a0 = $s0`, `$a1 = $v0 + 0x1BB0` and a sibling `j` to
 * `player_setDangerEdgeOtherSidePlanePoint`.
 * UNCONFIRMED: the AI work field meaning and the callee prototype.
 
 */
void *GetSCRCharaAIWorkPtr(void);
void player_setDangerEdgeOtherSidePlanePoint(void *arg, void *work);

void SetPlayerDangerEdgeOtherSidePlanePoint(void *arg) {
    player_setDangerEdgeOtherSidePlanePoint(arg, (char *)GetSCRCharaAIWorkPtr() + 0x1BB0);
}
