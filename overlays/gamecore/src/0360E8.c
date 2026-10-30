/* GAMECORE.XFF @ 0x0360E8 (48 B) - bootscelogoscript
 * Evidence: `lw $a0,%lo(ScriptSpriteMenuObjDef_SPRITE_SCE_LOGO_LAYOUT)` (a
 * pointer variable), `$a3 = $a0` (first parameter), `$t0 = $a1` (second
 * parameter), `$a1 = $a2 = $t1 = 0`, sibling `j` to `_SCRStartSpriteMenuAnim`.
 * UNCONFIRMED: the callee prototype and the parameter meanings.
 
 */
extern void *ScriptSpriteMenuObjDef_SPRITE_SCE_LOGO_LAYOUT;
void _SCRStartSpriteMenuAnim(void *def, int a, int b, int c, int d, int e);

void bootscelogoscript(int arg0, int arg1) {
    _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_SCE_LOGO_LAYOUT,
                            0, 0, arg0, arg1, 0);
}
