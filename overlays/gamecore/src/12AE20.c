/* GAMECORE.XFF @ 0x12AE20 (40 B) - SCRFuncSoundResetPlayerAttrInfo
 * Evidence: stores $ra, 0x0($sp); loads $a0, 0x0($v0), $ra, 0x0($sp); calls getSScriptWork, getPlayerColCont2, j ColCont2_EventAttrReset; frame
 
 */
int getSScriptWork(void);
char *getPlayerColCont2(int obj);
void ColCont2_EventAttrReset(unsigned char *p);

void SCRFuncSoundResetPlayerAttrInfo(void) {
    ColCont2_EventAttrReset(getPlayerColCont2(*(int *)getSScriptWork()));
}
