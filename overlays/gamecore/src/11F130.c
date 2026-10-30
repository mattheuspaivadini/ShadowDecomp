/* GAMECORE.XFF @ 0x11F130 (64 B) - SCRConditionLessPlayerLife
 * Evidence: stores $f20, 0x8($sp), $ra, 0x0($sp); loads $ra, 0x0($sp), $f20, 0x8($sp); calls getPlayerHpRatio; frame
 
 */
float getPlayerHpRatio(void);

int SCRConditionLessPlayerLife(float t) {
    return getPlayerHpRatio() * 100.0f <= t;
}
