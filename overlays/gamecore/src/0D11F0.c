/* GAMECORE.XFF @ 0x0D11F0 (48 B) - PauseMapStart
 * Evidence: `lw $a0,0x0(ScriptSpriteMenuObjDef_SPRITE_MAP_SMOKE_REND_LAYOUT)`, the
 * incoming $a0 forwarded to $a3, $a1/$a2/$t0/$t1 zeroed, tail `j
 * _SCRStartSpriteMenuAnim`.
 * UNCONFIRMED: none
 
 */
extern int ScriptSpriteMenuObjDef_SPRITE_MAP_SMOKE_REND_LAYOUT[];
int _SCRStartSpriteMenuAnim(int obj, int a1, int a2, int a3, int a4, int a5);

void PauseMapStart(int param) {
    _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_MAP_SMOKE_REND_LAYOUT[0],
                            0, 0, param, 0, 0);
}
