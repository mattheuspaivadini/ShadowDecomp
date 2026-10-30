/* GAMECORE.XFF @ 0x07B2F0 (52 B) - IsHorseCalled_withFlgOff
 * Evidence: `lbu $v1,0xD9C($a1)` (an unsigned char), `$a0 = 1`, a `bne`
 * against 1 with `$v0 = $v1` in the delay slot (always returns the old flag)
 * and `sb $zero,0xD9C` on the equal path.
 * UNCONFIRMED: the AI work field meaning.
 
 */
struct SCRCharaAIWork {
    char pad[0xD9C];
    unsigned char horseCalled;
};

struct SCRCharaAIWork *GetSCRCharaAIWorkPtr(void);

int IsHorseCalled_withFlgOff(void) {
    struct SCRCharaAIWork *work = GetSCRCharaAIWorkPtr();
    unsigned char flag = work->horseCalled;

    if (flag == 1)
        work->horseCalled = 0;
    return flag;
}
