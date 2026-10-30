/* GAMECORE.XFF @ 0x06BCE8 (44 B) - SCRConditionMinoCAtkCountChack
 * Evidence: `daddu $s0, $a1` in the `jal` delay slot, `lw 0x41E8($v0)` and
 * `slt $v0, $s0, $v0`: the second argument is compared against the AI work
 * attack counter.
 * UNCONFIRMED: the AI work field meaning and the first argument's role.
 
 */
void *GetSCRCharaAIWorkPtr(void);

int SCRConditionMinoCAtkCountChack(int unused, int count) {
    return count < *(int *)((char *)GetSCRCharaAIWorkPtr() + 0x41E8);
}
