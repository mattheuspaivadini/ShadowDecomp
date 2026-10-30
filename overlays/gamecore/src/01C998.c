/* GAMECORE.XFF @ 0x01C998 (36 B) - languageMenuUnload
 * Evidence: `$a0 = SH_StageDataDEFAULT`, `$a1 = 0x760`, `$a2 = 0`, sibling `j`
 * to `sheetMgrUnloadSegmentIndex`.
 * UNCONFIRMED: the segment index / flag argument meanings.
 
 */
extern int SH_StageDataDEFAULT[];
void sheetMgrUnloadSegmentIndex(void *data, int index, int flag);

void languageMenuUnload(void) {
    sheetMgrUnloadSegmentIndex(SH_StageDataDEFAULT, 0x760, 0);
}
