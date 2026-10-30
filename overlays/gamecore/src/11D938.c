/* GAMECORE.XFF @ 0x11D938 (60 B) - SCRConditionMyselfOverGlobalY
 * Evidence: stores $f20, 0x8($sp), $ra, 0x0($sp); loads $v1, 0x134($v0), $f0, 0x4($v1), $ra, 0x0($sp), $f20, 0x8($sp); calls GetLayoutClass; frame
 
 */
/* UNCONFIRMED: layout class +0x134 points at the world position; +0x04 is its
 * Y component.
 */
void *GetLayoutClass(void *obj);

int SCRConditionMyselfOverGlobalY(void *obj, float y) {
    char *layout = GetLayoutClass(obj);
    if (y <= *(float *)(*(char **)(layout + 0x134) + 4))
        return 1;
    return 0;
}
