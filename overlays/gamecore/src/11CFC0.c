/* GAMECORE.XFF @ 0x11CFC0 (40 B) - SCRConditionPlayerRidingHorse
 * Evidence: stores $ra, 0x0($sp); loads $a0, 0x4078($v0), $ra, 0x0($sp); calls getSCRDataCtrlWork, nico_GetPlayerCharacterRidingHorseObject; frame
 
 */
/* UNCONFIRMED: +0x4078 is the player object. */
char *getSCRDataCtrlWork(void);
void *nico_GetPlayerCharacterRidingHorseObject(void *player);

int SCRConditionPlayerRidingHorse(void) {
    char *work = getSCRDataCtrlWork();
    return nico_GetPlayerCharacterRidingHorseObject(*(void **)(work + 0x4078)) != 0;
}
