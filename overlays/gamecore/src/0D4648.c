/* GAMECORE.XFF @ 0x0D4648 (52 B) - demoManSkip
 * Evidence: `jal GetScriptLayoutClass`, `$s0 = $a1`, `jal SkipCutDemoCameraOrient` with
 * `$a0 = $s0`, then `jal CancelCaptionSubThreadAll`.
 * UNCONFIRMED: GetScriptLayoutClass argument/return types
 
 */
char *GetScriptLayoutClass(void);
void SkipCutDemoCameraOrient(int orient);
void CancelCaptionSubThreadAll(void);

void demoManSkip(int unused, int orient) {
    GetScriptLayoutClass();
    SkipCutDemoCameraOrient(orient);
    CancelCaptionSubThreadAll();
}
