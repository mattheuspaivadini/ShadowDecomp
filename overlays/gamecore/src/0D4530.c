/* GAMECORE.XFF @ 0x0D4530 (40 B) - demoManChkStart
 * Evidence: `lw $v1,0x2D8($v0)`, `lw $v0,0x44($v1)`, `sltu $v0,$zero,$v0`.
 * UNCONFIRMED: GetScriptLayoutClass argument/return types
 
 */
char *GetScriptLayoutClass(void);

int demoManChkStart(void) {
    return *(int *)(*(char **)(GetScriptLayoutClass() + 0x2D8) + 0x44) != 0;
}
