/* GAMECORE.XFF @ 0x1190F8 (44 B) - SCRFuncSetAttainRange
 * Evidence: stores $s0, 0x0($sp), $ra, 0x8($sp); loads $ra, 0x8($sp), $s0, 0x0($sp); calls getSCRDataCtrlWork, j setSCRAttainRange; frame
 
 */
/* UNCONFIRMED: only the 8th argument ($t3) is used as the range value. */
char *getSCRDataCtrlWork(void);
void setSCRAttainRange(char *work, int range);

void SCRFuncSetAttainRange(void *a0, void *a1, void *a2, void *a3, void *t0,
                           void *t1, void *t2, int range) {
    setSCRAttainRange(getSCRDataCtrlWork(), range);
}
