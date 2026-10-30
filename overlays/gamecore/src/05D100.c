/* GAMECORE.XFF @ 0x05D100 (52 B) - nico_resetHorseRidingStatusForHorse
 * Evidence: `lw $v1,0x4248($v0)` from the AI work, a zero test that returns
 * early, and a sibling `j` to `nico_resetHorseBridleTerminalParentPoint` with
 * `$a0 = $v1` in the delay slot.
 * UNCONFIRMED: the AI work field meaning and the callee prototype.
 
 */
struct SCRCharaAIWork {
    char pad[0x4248];
    int horseObj;
};

struct SCRCharaAIWork *GetSCRCharaAIWorkPtr(void);
void nico_resetHorseBridleTerminalParentPoint(int obj);

void nico_resetHorseRidingStatusForHorse(void) {
    struct SCRCharaAIWork *work = GetSCRCharaAIWorkPtr();

    if (work->horseObj != 0)
        nico_resetHorseBridleTerminalParentPoint(work->horseObj);
}
