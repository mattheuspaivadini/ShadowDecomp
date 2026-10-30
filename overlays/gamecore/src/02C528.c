/* GAMECORE.XFF @ 0x02C528 (64 B) - stagemanager_unloadstage
 * Evidence: `sd $ra` frame, `jal createScriptObj` with `$a0 = .text+0x2D648`
 * (lui/addiu %hi/%lo pair, i.e. a static function address, not a literal),
 * `$a1 = arg`, `$a2 = *(gcGlobalVar+0x308)`, `$a3 = 0x1000`, `$t0 = 0`,
 * `$t1 = 1`, `$t2 = 0`, `$t3 = 0` in the delay slot; `ld $ra` + `jr` after.
 * UNCONFIRMED: the static at 0x2D648 (script entry) and the argument meanings.
 */
void createScriptObj(void *script, void *arg, void *data, int a3, int a4,
                     int a5, int a6, int a7);
void func_0002D648(void);
extern char gcGlobalVar[];

void stagemanager_unloadstage(void *arg) {
    createScriptObj(func_0002D648, arg, *(void **)(gcGlobalVar + 0x308),
                    0x1000, 0, 1, 0, 0);
}
