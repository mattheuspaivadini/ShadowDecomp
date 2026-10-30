/* GAMECORE.XFF @ 0x0638E8 (52 B) - SCRFuncKnightSetShakeStop
 * Evidence: `lw $v0,0x41B0($v1)`, `$a0 = $v0 | 4`, `$v0 = $v0 & 4` and
 * `beql $v0,$zero` with the `sw $a0,0x41B0` in the likely delay slot, i.e. the
 * store only runs when bit 2 is clear.
 * UNCONFIRMED: the AI work field meaning.
 
 */
struct SCRCharaAIWork {
    char pad[0x41B0];
    int flags;
};

struct SCRCharaAIWork *GetSCRCharaAIWorkPtr(void);

void SCRFuncKnightSetShakeStop(void) {
    struct SCRCharaAIWork *work = GetSCRCharaAIWorkPtr();

    if ((work->flags & 4) == 0)
        work->flags |= 4;
}
