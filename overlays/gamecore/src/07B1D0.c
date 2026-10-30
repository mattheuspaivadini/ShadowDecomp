/* GAMECORE.XFF @ 0x07B1D0 (60 B) - getTorchInfo
 * Evidence: `jal GetSCRCharaAIWorkPtr`, then `lw 0x70($a0)` compared against
 * 9 with `$a1 = 0` in the branch delay slot; on the taken-not path
 * `lbu 0x94($a0)` feeds `sltu $a1,$zero,$v0`. The result is returned via $a1.
 * UNCONFIRMED: the AI work fields at +0x70 (state) and +0x94 (flag).
 
 */
void *GetSCRCharaAIWorkPtr(void);

int getTorchInfo(void) {
    char *work = GetSCRCharaAIWorkPtr();
    int result = 0;

    if (*(int *)(work + 0x70) == 9)
        result = *(unsigned char *)(work + 0x94) != 0;
    return result;
}
