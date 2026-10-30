/* GAMECORE.XFF @ 0x0419A8 (48 B) - bootChooseLangScript
 * Evidence: `lw $a0,%lo(ScriptSpriteMenuObjDef_SPRITE_CHOOSE_LANGUAGE_LAYOUT)`
 * (a pointer variable) with `$a1`..`$a3`/`$t0`/`$t1` all zero and a sibling
 * `j` to `_SCRStartSpriteMenuAnim`.
 * UNCONFIRMED: the callee prototype.
 
 */
extern void *ScriptSpriteMenuObjDef_SPRITE_CHOOSE_LANGUAGE_LAYOUT;
void _SCRStartSpriteMenuAnim(void *def, int a, int b, int c, int d, int e);

void bootChooseLangScript(void) {
    _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_CHOOSE_LANGUAGE_LAYOUT,
                            0, 0, 0, 0, 0);
}
