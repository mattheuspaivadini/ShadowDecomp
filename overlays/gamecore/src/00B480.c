/* GAMECORE.XFF @ 0x00B480 (40 B) - nico_ResetScriptCtrlAI
 * Evidence: `jal isysGetThisSubThread` with its result moved to `$a0` in the
 * delay slot of the following `jal CharaCtrlResetAllScriptCtrlStatus`, then
 * `jal scrRun` and a backward `b` to the first `jal` (an endless loop).
 * UNCONFIRMED: the callee prototypes (all appear argument-less / void).
 
 */
void *isysGetThisSubThread(void);
void CharaCtrlResetAllScriptCtrlStatus(void *thread);
void scrRun(void);

void nico_ResetScriptCtrlAI(void) {
    while (1) {
        CharaCtrlResetAllScriptCtrlStatus(isysGetThisSubThread());
        scrRun();
    }
}
