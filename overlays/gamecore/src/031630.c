/* GAMECORE.XFF @ 0x031630 (36 B) - demo_brige_resetHorseParent
 * Evidence: `$a0 = gcGlobalVar+0x2B4`, `jal SCRGetFirstObj`, then `$a0 = $v0`
 * and a sibling `j` to `nico_ResetPlayerHorseRidingControl`.
 * UNCONFIRMED: the gcGlobalVar field meaning and the callee prototype.
 
 */
extern char gcGlobalVar[];
void *SCRGetFirstObj(void *param);
void nico_ResetPlayerHorseRidingControl(void *obj);

void demo_brige_resetHorseParent(void) {
    nico_ResetPlayerHorseRidingControl(SCRGetFirstObj(gcGlobalVar + 0x2B4));
}
