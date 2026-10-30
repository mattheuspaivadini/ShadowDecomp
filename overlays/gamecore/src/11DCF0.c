/* GAMECORE.XFF @ 0x11DCF0 (32 B) - SCRConditionPlayerInSight
 * Evidence: ops ld lw sd; calls getSCRDataCtrlWork; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
char *getSCRDataCtrlWork(void);

int SCRConditionPlayerInSight(void) {
    return F(getSCRDataCtrlWork(), int, 0x405C);
}
