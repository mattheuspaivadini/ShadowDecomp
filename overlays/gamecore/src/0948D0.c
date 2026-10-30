/* GAMECORE.XFF @ 0x0948D0 (56 B) - SCRFuncPoseidonSetPlayerTerrLog
 * Evidence: `$s0 = $a1` in the `jal` delay slot, `$v0 = $a1-1`,
 * `sltiu $v0,$v0,2`, `bnel $v0,$zero` with `sw $s0,0x41CC($v1)` in the
 * branch delay slot.
 * UNCONFIRMED: the AI work field meaning and the 1/2 log values.
 
 */
struct SCRCharaAIWork {
    char pad[0x41CC];
    int f41CC;
};

struct SCRCharaAIWork *GetSCRCharaAIWorkPtr(void);

void SCRFuncPoseidonSetPlayerTerrLog(void *unused, int log) {
    struct SCRCharaAIWork *work = GetSCRCharaAIWorkPtr();

    if (log == 1 || log == 2)
        work->f41CC = log;
}
