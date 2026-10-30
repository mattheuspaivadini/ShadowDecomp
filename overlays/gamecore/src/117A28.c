/* GAMECORE.XFF @ 0x117A28 (40 B) - SCRFuncParentRelateInit
 * Evidence: stores $ra, 0x0($sp), $zero, 0x4($v0), $zero, 0x0($v0); loads $ra, 0x0($sp); calls getSCRDataCtrlWork; frame
 
 */
/* UNCONFIRMED: +0x40D8 is the parent relation work; both words are cleared. */
char *getSCRDataCtrlWork(void);

void SCRFuncParentRelateInit(void) {
    char *work = getSCRDataCtrlWork() + 0x40D8;
    *(int *)(work + 0x00) = 0;
    *(int *)(work + 0x04) = 0;
}
