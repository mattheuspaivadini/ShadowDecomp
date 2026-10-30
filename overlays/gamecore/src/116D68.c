/* GAMECORE.XFF @ 0x116D68 (44 B) - SCRFuncSetGpCalcDist
 * Evidence: stores $ra, 0x0($sp), $f20, 0x8($sp); loads $ra, 0x0($sp), $f20, 0x8($sp); calls getSCRDataCtrlWork, j setGpCalcDist; frame
 
 */
/* UNCONFIRMED: forwards the distance to the shared GP distance setter. */
char *getSCRDataCtrlWork(void);
void setGpCalcDist(char *work, float dist);

void SCRFuncSetGpCalcDist(float dist) {
    setGpCalcDist(getSCRDataCtrlWork(), dist);
}
