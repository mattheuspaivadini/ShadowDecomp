/* GAMECORE.XFF @ 0x074A60 (48 B) - OptionMenuStart
 * Evidence: `lw $a0,%lo(ScriptSpriteMenuObjDef_SPRITE_OPTION)` (a pointer
 * variable), `$a3 = $a0` (first parameter), `$t1 = $a1` (second parameter),
 * `$a1 = $a2 = $t0 = 0`, sibling `j` to `_SCRStartSpriteMenuAnim`.
 * UNCONFIRMED: the callee prototype and the parameter meanings.
 
 */
extern void *ScriptSpriteMenuObjDef_SPRITE_OPTION;
void _SCRStartSpriteMenuAnim(void *def, int a, int b, int c, int d, int e);

void OptionMenuStart(int arg0, int arg1) {
    _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_OPTION,
                            0, 0, arg0, 0, arg1);
}
