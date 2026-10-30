/* GAMECORE.XFF @ 0x0953C0 (48 B) - bootprogressivecheck
 * Evidence: `lw $a0,0x0(ScriptSpriteMenuObjDef_SPRITE_BOOT_PROGRESSIVE_ALERT)`,
 * the incoming $a0 forwarded to $a3, $a1/$a2/$t0/$t1 zeroed, tail `j
 * _SCRStartSpriteMenuAnim`.
 * UNCONFIRMED: argument meanings of _SCRStartSpriteMenuAnim
 
 */
extern int ScriptSpriteMenuObjDef_SPRITE_BOOT_PROGRESSIVE_ALERT[];
int _SCRStartSpriteMenuAnim(int obj, int a1, int a2, int a3, int a4, int a5);

void bootprogressivecheck(int param) {
    _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_BOOT_PROGRESSIVE_ALERT[0],
                            0, 0, param, 0, 0);
}
