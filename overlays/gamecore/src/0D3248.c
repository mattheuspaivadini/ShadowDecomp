/* GAMECORE.XFF @ 0x0D3248 (40 B) - SCRFuncYamoriBSetBreathVolume
 * Evidence: `jal GetSCRCharaAIWorkPtr`, `daddu $s0,$t2,$zero` (7th integer argument),
 * then `sw $s0 -> [v0+0x41CC]`.
 * UNCONFIRMED: the value arrives in $t2, i.e. it is the 7th argument; the six leading
 * arguments are never read
 
 */
char *GetSCRCharaAIWorkPtr(void);

void SCRFuncYamoriBSetBreathVolume(int a0, int a1, int a2, int a3, int a4, int a5,
                                   int value) {
    *(int *)(GetSCRCharaAIWorkPtr() + 0x41CC) = value;
}
