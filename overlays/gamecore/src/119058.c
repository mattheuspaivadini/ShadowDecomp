/* GAMECORE.XFF @ 0x119058 (60 B) - SCRFuncSetPassageRangeData
 * Evidence: stores $ra, 0x0($sp), $f21, 0x10($sp), $f20, 0x8($sp); loads $f21, 0x10($sp), $ra, 0x0($sp), $f20, 0x8($sp); calls getSCRDataCtrlWork, j setPassageRangeData; frame
 
 */
/* UNCONFIRMED: forwards both range values to the shared setter. */
char *getSCRDataCtrlWork(void);
void setPassageRangeData(char *work, float a, float b);

void SCRFuncSetPassageRangeData(float a, float b) {
    setPassageRangeData(getSCRDataCtrlWork(), a, b);
}
