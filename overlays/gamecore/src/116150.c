/* GAMECORE.XFF @ 0x116150 (32 B) - SCRFuncResetPathSystem
 * Evidence: ops ld sd; calls getSCRDataCtrlWork, j resetPassageWork; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
char *getSCRDataCtrlWork(void);
void resetPassageWork(char *w);

void SCRFuncResetPathSystem(void) {
    resetPassageWork(getSCRDataCtrlWork());
}
