/* GAMECORE.XFF @ 0x03ECD8 (40 B) - setBossAbsoluteDeath
 * Evidence: `jal GetSCRCharaAIWorkPtr`, `lw $v1, 0($v0)` (a pointer) then
 * `li $a0, 1` + `sw $a0, 0x48($v1)`.
 * UNCONFIRMED: both field meanings and the callee prototype.
 
 */
void *GetSCRCharaAIWorkPtr(void);

void setBossAbsoluteDeath(void) {
    *(int *)(*(char **)GetSCRCharaAIWorkPtr() + 0x48) = 1;
}
