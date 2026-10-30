/* GAMECORE.XFF @ 0x07D288 (44 B) - nico_setPlayerGripPoint
 * Evidence: `$a0` is saved in `$s0` across `jal GetSCRCharaAIWorkPtr`, then
 * `$a0 = $s0`, `$a1 = $v0 + 0x1AC0` and a sibling `j` to
 * `player_setGripHangPointGeometry`.
 * UNCONFIRMED: the AI work field meaning and the callee prototype.
 
 */
void *GetSCRCharaAIWorkPtr(void);
void player_setGripHangPointGeometry(void *arg, void *work);

void nico_setPlayerGripPoint(void *arg) {
    player_setGripHangPointGeometry(arg, (char *)GetSCRCharaAIWorkPtr() + 0x1AC0);
}
