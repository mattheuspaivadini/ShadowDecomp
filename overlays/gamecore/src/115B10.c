/* GAMECORE.XFF @ 0x115B10 (48 B) - SCRFuncLineSetRoute
 * Evidence: stores $s0, 0x0($sp), $ra, 0x8($sp); loads $ra, 0x8($sp), $s0, 0x0($sp); calls getSCRDataCtrlWork, j setEventLineAttr; frame
 
 */
/* UNCONFIRMED: line attribute bit mask 2 = "route". */
char *getSCRDataCtrlWork(void);
void setEventLineAttr(char *work, int line, int attr);

void SCRFuncLineSetRoute(void *unused, int line) {
    setEventLineAttr(getSCRDataCtrlWork(), line, 2);
}
