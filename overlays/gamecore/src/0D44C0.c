/* GAMECORE.XFF @ 0x0D44C0 (36 B) - demoManBootChk
 * Evidence: `jal GetScriptLayoutClass`, `lw $v1,0x2D8($v0)`, `lw $v0,0x8($v1)`.
 * UNCONFIRMED: GetScriptLayoutClass argument/return types
 
 */
char *GetScriptLayoutClass(void);

int demoManBootChk(void) {
    return *(int *)(*(char **)(GetScriptLayoutClass() + 0x2D8) + 8);
}
