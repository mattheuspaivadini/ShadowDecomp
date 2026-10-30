/* GAMECORE.XFF @ 0x11F7D0 (24 B) - SCRConditionSegmentLoad
 * Evidence: ops ld lw sd; calls j stagemanager_checkstageAlreadyLoadedByStrptr; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
int stagemanager_checkstageAlreadyLoadedByStrptr(int s);
int SCRConditionSegmentLoad(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8) {
    return stagemanager_checkstageAlreadyLoadedByStrptr(a8);
}
