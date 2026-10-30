/* GAMECORE.XFF @ 0x0D36E0 (48 B) - SCRConditionYamoriBBellyDamageCheck
 * Evidence: `$s0 = $a1`, `lw [v0+0x41E0]`, `slt $v0,$v0,$s0`, `xori $v0,$v0,1`.
 * UNCONFIRMED: none
 
 */
char *GetSCRCharaAIWorkPtr(void);

int SCRConditionYamoriBBellyDamageCheck(int unused, int value) {
    return !(*(int *)(GetSCRCharaAIWorkPtr() + 0x41E0) < value);
}
