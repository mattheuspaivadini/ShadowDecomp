/* GAMECORE.XFF @ 0x06E800 (48 B) - SCRConditionNargaWallCheck
 * Evidence: `$a1` saved in `$s0`, `jal GetSCRCharaAIWorkPtr`, then
 * `xor $s0,$s0,$v1` against `0x5AA0($v0)` and `sltiu $v0,$s0,1`
 * (an `==` compare).
 * UNCONFIRMED: the AI work field meaning.
 
 */
struct SCRCharaAIWork {
    char pad[0x5AA0];
    int f5AA0;
};

struct SCRCharaAIWork *GetSCRCharaAIWorkPtr(void);

int SCRConditionNargaWallCheck(int unused, int value) {
    return value == GetSCRCharaAIWorkPtr()->f5AA0;
}
