/* GAMECORE.XFF @ 0x02CA70 (20 B) - stagemanager_checkstageAlreadyLoaded
 * Shape `tail-call` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: frame whose only work is a single tail `j`.
 */
void stagemanager_checkstageAlreadyLoaded(void) {
    sheetMgrChkStageIndexResolve();
}
