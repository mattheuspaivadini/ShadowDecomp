/* GAMECORE.XFF @ 0x0EB800 (52 B) - get_boss_subjective_camera_lws_animation_param
 * Evidence: stores $ra, 0x0($sp); loads $v0, 0x11F4($v0), $ra, 0x0($sp); calls GAMEUTIL_get_boss_obj, GetScriptCharacterClass; frame
 
 */
/* UNCONFIRMED: 0x11F4 of the boss script character class holds the LWS param id. */
void *GAMEUTIL_get_boss_obj(void);
void *GetScriptCharacterClass(void *p);

int get_boss_subjective_camera_lws_animation_param(void) {
    void *boss = GAMEUTIL_get_boss_obj();
    if (boss == 0)
        return 0;
    return *(int *)((char *)GetScriptCharacterClass(boss) + 0x11F4);
}
