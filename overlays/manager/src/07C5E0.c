/* MANAGER.XFF @ 0x07C5E0 (8 B) - SetGameLightUserParam
 * Evidence: `jr $ra` with `ac850050` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
void SetGameLightUserParam(unsigned char *p, int value) {
    *(int *)(p + 0x50) = value;
}
