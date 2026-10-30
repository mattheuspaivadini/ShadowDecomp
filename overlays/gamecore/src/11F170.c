/* GAMECORE.XFF @ 0x11F170 (52 B) - SCRConditionOverPlayerGrip
 * Evidence: stores $f20, 0x8($sp), $ra, 0x0($sp); loads $ra, 0x0($sp), $f20, 0x8($sp); calls getPlayerGrip; frame
 
 */
float getPlayerGrip(void);

int SCRConditionOverPlayerGrip(float t) {
    return t <= getPlayerGrip();
}
