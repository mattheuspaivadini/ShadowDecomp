/* GAMECORE.XFF @ 0x07D258 (44 B) - nico_setPlayerEdgePoint
 * Evidence: `$a0` is saved in `$s0` across `jal GetSCRCharaAIWorkPtr`, then
 * `$a0 = $s0`, `$a1 = $v0 + 0x1AC0` and a sibling `j` to
 * `player_setEdgeHangPointGeometry`.
 * UNCONFIRMED: the AI work field meaning and the callee prototype.
 
 */
void *GetSCRCharaAIWorkPtr(void);
void player_setEdgeHangPointGeometry(void *arg, void *work);

void nico_setPlayerEdgePoint(void *arg) {
    player_setEdgeHangPointGeometry(arg, (char *)GetSCRCharaAIWorkPtr() + 0x1AC0);
}
