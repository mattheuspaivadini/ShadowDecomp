/* GAMECORE.XFF @ 0x05C310 (60 B) - SCRFuncHorseInterestMain
 * Evidence: `$s0 = $a0`, `$s1 = $t1` (6th argument) in the `jal` delay slot,
 * then a tail `j updateInterestWork` with `$a0 = arg0`,
 * `$a1 = GetSCRCharaAIWorkPtr() + 0x41B0`, `$a2 = arg5`.
 * UNCONFIRMED: the AI work field and the callback's argument roles.
 
 */
struct SCRCharaAIWork {
    char pad[0x41B0];
    int f41B0;
};

struct SCRCharaAIWork *GetSCRCharaAIWorkPtr(void);
void updateInterestWork(void *arg0, void *work, int arg5);

void SCRFuncHorseInterestMain(void *arg0, int arg1, int arg2, int arg3, int arg4,
                              int arg5) {
    updateInterestWork(arg0, (char *)GetSCRCharaAIWorkPtr() + 0x41B0, arg5);
}
