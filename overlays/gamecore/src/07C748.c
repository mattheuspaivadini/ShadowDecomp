/* GAMECORE.XFF @ 0x07C748 (32 B) - sendArrowInfo
 * Evidence: jal GetSCRCharaAIWorkPtr, lw field
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
char *GetSCRCharaAIWorkPtr(void);

int sendArrowInfo(void) {
    return F(GetSCRCharaAIWorkPtr(), int, 0x20);
}
