/* MANAGER.XFF @ 0x07C5E8 (8 B) - SetGameLightUserFunc
 * Evidence: `jr $ra` with `ac850054` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
void SetGameLightUserFunc(unsigned char *p, int value) {
    *(int *)(p + 0x54) = value;
}
