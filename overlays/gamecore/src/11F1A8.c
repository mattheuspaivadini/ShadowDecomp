/* GAMECORE.XFF @ 0x11F1A8 (52 B) - SCRConditionLessPlayerGrip
 * Evidence: stores $f20, 0x8($sp), $ra, 0x0($sp); loads $ra, 0x0($sp), $f20, 0x8($sp); calls getPlayerGrip; frame
 
 */
float getPlayerGrip(void);

int SCRConditionLessPlayerGrip(float t) {
    return getPlayerGrip() <= t;
}
