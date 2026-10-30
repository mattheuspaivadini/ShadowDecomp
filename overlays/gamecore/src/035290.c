/* GAMECORE.XFF @ 0x035290 (56 B) - SCRConditionBirdBeginningApproaching
 * Evidence: no loads/stores; calls GetSCRCharaAIWorkPtr
 */
/* variant c: reversed comparison b > a */
struct SCRCharaAIWork {
    char pad[0x41D4];
    float f41D4;
    float f41D8;
};

struct SCRCharaAIWork *GetSCRCharaAIWorkPtr(void);

int SCRConditionBirdBeginningApproaching(void) {
    struct SCRCharaAIWork *work = GetSCRCharaAIWorkPtr();

    return work->f41D8 > work->f41D4;
}
