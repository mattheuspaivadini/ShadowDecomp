/* GAMECORE.XFF @ 0x11D978 (60 B) - SCRConditionMyselfLessGlobalY
 * Evidence: stores $f20, 0x8($sp), $ra, 0x0($sp); loads $v1, 0x134($v0), $f0, 0x4($v1), $ra, 0x0($sp), $f20, 0x8($sp); calls GetLayoutClass; frame
 
 */
/* UNCONFIRMED: mirror of SCRConditionMyselfOverGlobalY. */
void *GetLayoutClass(void *obj);

int SCRConditionMyselfLessGlobalY(void *obj, float y) {
    char *layout = GetLayoutClass(obj);
    if (*(float *)(*(char **)(layout + 0x134) + 4) <= y)
        return 1;
    return 0;
}
