/* GAMECORE.XFF @ 0x115B40 (48 B) - SCRFuncLineUnsetRoute
 * Evidence: stores $s0, 0x0($sp), $ra, 0x8($sp); loads $ra, 0x8($sp), $s0, 0x0($sp); calls getSCRDataCtrlWork, j unsetEventLineAttr; frame
 
 */
/* UNCONFIRMED: line attribute bit mask 2 = "route", cleared here. */
char *getSCRDataCtrlWork(void);
void unsetEventLineAttr(char *work, int line, int attr);

void SCRFuncLineUnsetRoute(void *unused, int line) {
    unsetEventLineAttr(getSCRDataCtrlWork(), line, 2);
}
