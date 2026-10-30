/* GAMECORE.XFF @ 0x062ED0 (56 B) - SCRConditionFallRockChack
 * Evidence: `lwc1 $f1,0x41B4($v0)`, `mtc1 $zero,$f0`, `c.lt.s $f0,$f1`,
 * `bc1t` with `$v1 = 1` in the delay slot, `$v1 = 0` on the fall-through.
 * UNCONFIRMED: the AI work field meaning.
 
 */
struct SCRCharaAIWork {
    char pad[0x41B4];
    float f41B4;
};

struct SCRCharaAIWork *GetSCRCharaAIWorkPtr(void);

int SCRConditionFallRockChack(void) {
    struct SCRCharaAIWork *work = GetSCRCharaAIWorkPtr();

    return 0.0f < work->f41B4;
}
