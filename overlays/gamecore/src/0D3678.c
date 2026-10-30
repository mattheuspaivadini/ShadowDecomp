/* GAMECORE.XFF @ 0x0D3678 (44 B) - SCRFuncYamoriBSetBellyDamageInitWork
 * Evidence: `lwc1 $f0,0x4E74(<.rodata>)`, then `sw $zero -> [v0+0x41E0]` and
 * `swc1 $f0 -> [v0+0x41E4]`.
 * UNCONFIRMED: the rodata float value and the field meanings
 
 */
char *GetSCRCharaAIWorkPtr(void);
extern float D_kernel_rodata_4E74[];

void SCRFuncYamoriBSetBellyDamageInitWork(void) {
    char *p = GetSCRCharaAIWorkPtr();
    *(int *)(p + 0x41E0) = 0;
    *(float *)(p + 0x41E4) = D_kernel_rodata_4E74[0];
}
