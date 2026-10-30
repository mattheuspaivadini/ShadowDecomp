/* GAMECORE.XFF @ 0x02CD88 (36 B) - stagemanager_loadstage_nowait_norefcount
 * Evidence: `$a0 -> $a1`, `$a0 = SH_StageDataDEFAULT`, `$a2 = 0`, sibling `j`
 * to `sheetMgrLoadSegmentIndex`.
 * UNCONFIRMED: the callee prototype and the forwarded argument meaning.
 
 */
extern int SH_StageDataDEFAULT[];
void sheetMgrLoadSegmentIndex(void *data, int index, int flag);

void stagemanager_loadstage_nowait_norefcount(int index) {
    sheetMgrLoadSegmentIndex(SH_StageDataDEFAULT, index, 0);
}
