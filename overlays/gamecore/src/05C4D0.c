/* GAMECORE.XFF @ 0x05C4D0 (56 B) - SCRConditionOverHorseLife
 * Evidence: float arg saved to `$f20` in the `jal` delay slot, then
 * `c.le.s $f20,0x4220($v0)` with `bc1t` and `$v0 = 1` in the delay slot.
 * UNCONFIRMED: the AI work field meaning.
 
 */
struct SCRCharaAIWork {
    char pad[0x4220];
    float f4220;
};

struct SCRCharaAIWork *GetSCRCharaAIWorkPtr(void);

int SCRConditionOverHorseLife(float life) {
    struct SCRCharaAIWork *work = GetSCRCharaAIWorkPtr();

    return life <= work->f4220;
}
