/* GAMECORE.XFF @ 0x041620 (48 B) - SCRCerberusEventLineCut
 * Evidence: `$a1` is saved in `$s0` across `jal GetSCRCharaAIWorkPtr`, then
 * `$a0 = $v0 + 0x10`, `$a1 = $s0`, `$a2 = 4` and a sibling `j` to
 * `setEventLineAttr` (the first parameter is unused).
 * UNCONFIRMED: the AI work field meaning and the callee prototype.
 
 */
void *GetSCRCharaAIWorkPtr(void);
void setEventLineAttr(void *work, int arg, int count);

void SCRCerberusEventLineCut(int unused, int arg) {
    setEventLineAttr((char *)GetSCRCharaAIWorkPtr() + 0x10, arg, 4);
}
