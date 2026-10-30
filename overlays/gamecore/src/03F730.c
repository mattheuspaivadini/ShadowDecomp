/* GAMECORE.XFF @ 0x03F730 (40 B) - SCRFuncBuddhaMissileInit
 * Evidence: `jal GetSCRCharaAIWorkPtr`, then a `.rodata+0x110C` float (the %lo
 * addend rides on the `lwc1`) copied into AI work +0x41B4.
 * UNCONFIRMED: the AI work field meaning and the .rodata constant's name.
 
 */
extern char D_kernel_rodata_0000[];
void *GetSCRCharaAIWorkPtr(void);

void SCRFuncBuddhaMissileInit(void) {
    *(float *)((char *)GetSCRCharaAIWorkPtr() + 0x41B4) =
        *(float *)(D_kernel_rodata_0000 + 0x110C);
}
