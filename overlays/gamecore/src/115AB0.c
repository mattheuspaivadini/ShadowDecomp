/* GAMECORE.XFF @ 0x115AB0 (48 B) - SCRFuncLineCut
 * Evidence: stores $s0, 0x0($sp), $ra, 0x8($sp); loads $ra, 0x8($sp), $s0, 0x0($sp); calls getSCRDataCtrlWork, j setEventLineAttr; frame
 
 */
/* UNCONFIRMED: line attribute bit mask 4 = "cut". */
char *getSCRDataCtrlWork(void);
void setEventLineAttr(char *work, int line, int attr);

void SCRFuncLineCut(void *unused, int line) {
    setEventLineAttr(getSCRDataCtrlWork(), line, 4);
}
