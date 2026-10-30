/* GAMECORE.XFF @ 0x07C718 (48 B) - sendArrowPos
 * Evidence: `$a0` saved in `$s0`, `$a0 = $a1` in the delay slot of
 * `jal GetSCRCharaAIWorkPtr`, then `lq $v1,0x10($v0)` and `sq $v1,0($s0)`
 * (one 128-bit copy).
 * UNCONFIRMED: the AI work field meaning and the argument roles.
 
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));

struct SCRCharaAIWork {
    char pad[0x10];
    u_long128 pos;
};

struct SCRCharaAIWork *GetSCRCharaAIWorkPtr(int obj);

void sendArrowPos(void *dst, int obj) {
    *(u_long128 *)dst = GetSCRCharaAIWorkPtr(obj)->pos;
}
