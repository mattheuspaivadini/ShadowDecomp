/* GAMECORE.XFF @ 0x11FD68 (32 B) - SCRConditionReturnStartMyself
 * Evidence: ops ld lw sd; calls getSCRDataCtrlWork; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
char *getSCRDataCtrlWork(void);

int SCRConditionReturnStartMyself(void) {
    return F(getSCRDataCtrlWork(), int, 0x4198);
}
