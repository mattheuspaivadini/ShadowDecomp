/* GAMECORE.XFF @ 0x03ECA8 (44 B) - SCRGetBossTypeDef
 * Evidence: `jal GetSCRCharaAIWorkPtr`, `lw $v1, 0($v0)` then `beqz` skipping
 * the `lw $v0, 0($v1)`; 0 is returned when the pointer is null.
 * UNCONFIRMED: both field meanings and the callee prototype.
 
 */
void *GetSCRCharaAIWorkPtr(void);

void *SCRGetBossTypeDef(void) {
    char *p = *(char **)GetSCRCharaAIWorkPtr();

    if (p != 0) {
        return *(void **)p;
    }
    return 0;
}
