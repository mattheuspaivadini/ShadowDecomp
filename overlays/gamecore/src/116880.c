/* GAMECORE.XFF @ 0x116880 (32 B) - SCRFuncResetVolumeTime0
 * Evidence: ops ld sd sw; calls getSCRDataCtrlWork; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
char *getSCRDataCtrlWork(void);

void SCRFuncResetVolumeTime0(void) {
    F(getSCRDataCtrlWork(), int, 0x40AC) = 0;
}
