/* GAMECORE.XFF @ 0x0BBF08 (36 B) - SCRFuncSnakeCDeflateEnd
 * Evidence: stores $ra, 0x0($sp), $v1, 0x5A8C($v0); loads $ra, 0x0($sp); calls GetSCRCharaAIWorkPtr; frame
 
 */
char *GetSCRCharaAIWorkPtr(void);

void SCRFuncSnakeCDeflateEnd(void) {
    *(int *)(GetSCRCharaAIWorkPtr() + 0x5A8C) = 1;
}
