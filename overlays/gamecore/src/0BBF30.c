/* GAMECORE.XFF @ 0x0BBF30 (36 B) - SCRFuncSnakeCUpGroundInit
 * Evidence: stores $ra, 0x0($sp), $v1, 0x5A90($v0); loads $ra, 0x0($sp); calls GetSCRCharaAIWorkPtr; frame
 
 */
char *GetSCRCharaAIWorkPtr(void);

void SCRFuncSnakeCUpGroundInit(void) {
    *(int *)(GetSCRCharaAIWorkPtr() + 0x5A90) = 1;
}
