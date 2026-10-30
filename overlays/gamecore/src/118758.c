/* GAMECORE.XFF @ 0x118758 (44 B) - SCRFuncSetSearchRadius
 * Evidence: stores $ra, 0x0($sp), $f20, 0x8($sp); loads $ra, 0x0($sp), $f20, 0x8($sp); calls getSCRDataCtrlWork, j setSearchRadius; frame
 
 */
/* UNCONFIRMED: forwards the radius to setSearchRadius on the script work. */
char *getSCRDataCtrlWork(void);
void setSearchRadius(char *work, float radius);

void SCRFuncSetSearchRadius(float radius) {
    setSearchRadius(getSCRDataCtrlWork(), radius);
}
