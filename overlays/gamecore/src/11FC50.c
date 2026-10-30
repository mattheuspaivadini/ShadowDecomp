/* GAMECORE.XFF @ 0x11FC50 (44 B) - SCRConditionCheckGameClearCnt
 * Evidence: stores $s0, 0x0($sp), $ra, 0x8($sp); loads $s0, 0x0($sp), $ra, 0x8($sp); calls getGameClearCnt; frame
 
 */
int getGameClearCnt(void);

int SCRConditionCheckGameClearCnt(void *unused, int num) {
    return getGameClearCnt() >= num;
}
