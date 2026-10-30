/* GAMECORE.XFF @ 0x05C598 (56 B) - SCRConditionHorseEscapeCounterChack
 * Evidence: `lwc1 $f1,0x422C($v0)`, `mtc1 $zero,$f0`, `c.lt.s $f0,$f1`,
 * `bc1t` with `$v1 = 1` in the delay slot, `$v1 = 0` on the fall-through.
 * UNCONFIRMED: the AI work field meaning.
 
 */
struct SCRCharaAIWork {
    char pad[0x422C];
    float f422C;
};

struct SCRCharaAIWork *GetSCRCharaAIWorkPtr(void);

int SCRConditionHorseEscapeCounterChack(void) {
    struct SCRCharaAIWork *work = GetSCRCharaAIWorkPtr();

    return 0.0f < work->f422C;
}
