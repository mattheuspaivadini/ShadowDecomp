/* GAMECORE.XFF @ 0x0D1220 (52 B) - execPause
 * Evidence: same as PauseMapStart but $a3 = <.data>+0x1B40.
 * UNCONFIRMED: none
 
 */
extern int ScriptSpriteMenuObjDef_SPRITE_MAP_SMOKE_REND_LAYOUT[];
extern char D_kernel_data_1B40[];
int _SCRStartSpriteMenuAnim(int obj, int a1, int a2, int a3, int a4, int a5);

void execPause(void) {
    _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_MAP_SMOKE_REND_LAYOUT[0],
                            0, 0, (int)D_kernel_data_1B40, 0, 0);
}
