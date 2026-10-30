/* GAMECORE.XFF @ 0x05C630 (36 B) - SRCConditionHorseBossChackAll
 * Evidence: `$a0 = gcGlobalVar+0x2B8`, `jal SCRGetFirstObj`, then
 * `sltu $v0, $zero, $v0` (result != 0) in the return slot.
 * UNCONFIRMED: the gcGlobalVar field meaning and the callee prototype.
 
 */
extern char gcGlobalVar[];
void *SCRGetFirstObj(void *param);

int SRCConditionHorseBossChackAll(void) {
    return SCRGetFirstObj(gcGlobalVar + 0x2B8) != 0;
}
