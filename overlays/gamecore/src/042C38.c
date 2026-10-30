/* GAMECORE.XFF @ 0x042C38 (44 B) - SCRRequestMotionDirect
 * Evidence: `beqz $a1` skips the whole body; otherwise `lw $a1, 4($a1)` and a
 * sibling `j` to `CharaCtrlSetScriptCtrlStatus` with `$a0` unchanged.
 * UNCONFIRMED: the motion field meaning and the callee prototype.
 
 */
void CharaCtrlSetScriptCtrlStatus(int chr, int status);

void SCRRequestMotionDirect(int chr, void *motion) {
    if (motion != 0) {
        CharaCtrlSetScriptCtrlStatus(chr, *(int *)((char *)motion + 4));
    }
}
