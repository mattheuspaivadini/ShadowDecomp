/* GAMECORE.XFF @ 0x07D318 (52 B) - SetPlayerDangerEdgeOtherSidePlanePointWithInertiaRot
 * Evidence: `$a0` saved in `$s0`, `jal GetSCRCharaAIWorkPtr`, then
 * `$a1 = $v0 + 0x1BB0` with `$a0 = $s0` in the `jal
 * player_setDangerEdgeOtherSidePlanePoint` delay slot, then a sibling `j` to
 * `SetInertiaRotInterpMode` with `$a0 = $s0`.
 * UNCONFIRMED: the AI work field meaning and the callee prototypes.
 
 */
void *GetSCRCharaAIWorkPtr(void);
void player_setDangerEdgeOtherSidePlanePoint(void *arg, void *work);
void SetInertiaRotInterpMode(void *arg);

void SetPlayerDangerEdgeOtherSidePlanePointWithInertiaRot(void *arg) {
    player_setDangerEdgeOtherSidePlanePoint(
        arg, (char *)GetSCRCharaAIWorkPtr() + 0x1BB0);
    SetInertiaRotInterpMode(arg);
}
