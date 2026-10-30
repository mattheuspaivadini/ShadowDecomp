/* GAMECORE.XFF @ 0x1192D0 (44 B) - SCRFuncSetCreateTempAttain
 * Evidence: stores $s0, 0x0($sp), $ra, 0x8($sp); loads $ra, 0x8($sp), $s0, 0x0($sp); calls getSCRDataCtrlWork, j setCreateTempAttain; frame
 
 */
/* UNCONFIRMED: forwards the 2nd argument to the temporary attain setter. */
char *getSCRDataCtrlWork(void);
void setCreateTempAttain(char *work, int value);

void SCRFuncSetCreateTempAttain(void *unused, int value) {
    setCreateTempAttain(getSCRDataCtrlWork(), value);
}
