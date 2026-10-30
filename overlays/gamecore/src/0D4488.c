/* GAMECORE.XFF @ 0x0D4488 (56 B) - demoManBootRequest
 * Evidence: `jal GetScriptLayoutClass`, `lw $s0,0x2D8($v0)`, `jal
 * SetDisplayModelNearClippingSwitch` with `$a0 = 0`, then `sw 1 -> 0x4($s0)`.
 * UNCONFIRMED: GetScriptLayoutClass argument/return types
 
 */
char *GetScriptLayoutClass(void);
void SetDisplayModelNearClippingSwitch(int on);

void demoManBootRequest(void) {
    int *p = *(int **)(GetScriptLayoutClass() + 0x2D8);
    SetDisplayModelNearClippingSwitch(0);
    p[1] = 1;
}
