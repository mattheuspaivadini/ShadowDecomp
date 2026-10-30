/* GAMECORE.XFF @ 0x035258 (56 B) - SCRConditionBirdPassingEachOther
 * Evidence: `c.lt.s $f0,0x41D8($v0);$f1,0x41D4($v0)` (i.e. 0x41D8 < 0x41D4),
 * `bc1t` with `$v1 = 1` in the delay slot and `$v1 = 0` on the fall-through,
 * then `$v0 = $v1`.
 * UNCONFIRMED: the AI work field meanings.
 
 */
struct SCRCharaAIWork {
    char pad[0x41D4];
    float f41D4;
    float f41D8;
};

struct SCRCharaAIWork *GetSCRCharaAIWorkPtr(void);

int SCRConditionBirdPassingEachOther(void) {
    struct SCRCharaAIWork *work = GetSCRCharaAIWorkPtr();

    return work->f41D8 < work->f41D4;
}
