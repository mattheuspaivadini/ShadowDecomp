/* GAMECORE.XFF @ 0x095CA0 (40 B) - CheckSCRCharaAIWorkPtr
 * Evidence: `v0 = 0`, `beqz $a0` skips, `jal GetScriptCharacterClass`, then
 * `lw [v0+0x1200]`.
 * UNCONFIRMED: none
 
 */
char *GetScriptCharacterClass(int obj);

void *CheckSCRCharaAIWorkPtr(int obj) {
    if (obj == 0) {
        return 0;
    }
    return *(void **)(GetScriptCharacterClass(obj) + 0x1200);
}
