/* GAMECORE.XFF @ 0x11F0F0 (64 B) - SCRConditionOverPlayerLife
 * Evidence: stores $f20, 0x8($sp), $ra, 0x0($sp); loads $ra, 0x0($sp), $f20, 0x8($sp); calls getPlayerHpRatio; frame
 
 */
float getPlayerHpRatio(void);

int SCRConditionOverPlayerLife(float t) {
    return t <= getPlayerHpRatio() * 100.0f;
}
