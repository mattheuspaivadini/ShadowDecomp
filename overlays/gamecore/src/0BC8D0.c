/* GAMECORE.XFF @ 0x0BC8D0 (64 B) - ScrSpriteParamEnd
 * Evidence: stores $ra, 0x0($sp), $v0, 0x0($v1); loads $v1, 0x0($a2), $v0, 0xC($a2), $ra, 0x0($sp); frame
 
 */
void ScrSpriteParamEnd(char *p, void *arg) {
    if (*(int **)p != 0)
        **(int **)p = 1;
    if (*(void (**)(void *))(p + 0xC) != 0)
        (*(void (**)(void *))(p + 0xC))(arg);
}
