/* GAMECORE.XFF @ 0x115B70 (48 B) - SCRFuncLineSetForcePrio
 * Evidence: stores $s0, 0x0($sp), $ra, 0x8($sp); loads $ra, 0x8($sp), $s0, 0x0($sp); calls getSCRDataCtrlWork, j setEventLinePrio; frame
 
 */
/* UNCONFIRMED: priority 0x81 = forced top priority. */
char *getSCRDataCtrlWork(void);
void setEventLinePrio(char *work, int line, int prio);

void SCRFuncLineSetForcePrio(void *unused, int line) {
    setEventLinePrio(getSCRDataCtrlWork(), line, 0x81);
}
