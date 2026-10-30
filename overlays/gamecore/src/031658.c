/* GAMECORE.XFF @ 0x031658 (36 B) - demo_brige_resetHorseBridle
 * Evidence: `$a0 = gcGlobalVar+0x2B4`, `jal SCRGetFirstObj`, then `$a0 = $v0`
 * and a sibling `j` to `nico_resetHorseRidingStatusForHorse`.
 * UNCONFIRMED: the gcGlobalVar field meaning and the callee prototype.
 
 */
extern char gcGlobalVar[];
void *SCRGetFirstObj(void *param);
void nico_resetHorseRidingStatusForHorse(void *obj);

void demo_brige_resetHorseBridle(void) {
    nico_resetHorseRidingStatusForHorse(SCRGetFirstObj(gcGlobalVar + 0x2B4));
}
