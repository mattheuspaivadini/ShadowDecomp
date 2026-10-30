/* GAMECORE.XFF @ 0x115AE0 (48 B) - SCRFuncLineConnect
 * Evidence: stores $s0, 0x0($sp), $ra, 0x8($sp); loads $ra, 0x8($sp), $s0, 0x0($sp); calls getSCRDataCtrlWork, j unsetEventLineAttr; frame
 
 */
/* UNCONFIRMED: line attribute bit mask 4 = "cut", cleared here. */
char *getSCRDataCtrlWork(void);
void unsetEventLineAttr(char *work, int line, int attr);

void SCRFuncLineConnect(void *unused, int line) {
    unsetEventLineAttr(getSCRDataCtrlWork(), line, 4);
}
