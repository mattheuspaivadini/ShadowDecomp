/* GAMECORE.XFF @ 0x12B180 (56 B) - SCREventConditionPlayerRidingHorse
 * Evidence: stores $ra, 0x0($sp); loads $v1, 0x0($v0), $ra, 0x0($sp); calls getSScriptWork, nico_GetPlayerCharacterRidingHorseObject; frame
 * The image zeroes $v0 before the branch and shares one `sltu` after the join,
 * which is the early-return form below.
 
 */
int getSScriptWork(void);
int nico_GetPlayerCharacterRidingHorseObject(int obj);

int SCREventConditionPlayerRidingHorse(void) {
    int horse = *(int *)getSScriptWork();
    if (horse != 0)
        return nico_GetPlayerCharacterRidingHorseObject(horse) != 0;
    return 0;
}
