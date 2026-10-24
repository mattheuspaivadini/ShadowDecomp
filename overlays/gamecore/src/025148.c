/* GAMECORE.XFF @ 0x025148 (8 B) - getSpecialEffectObjWork
 * Evidence: `jr $ra` with `8c820030` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int getSpecialEffectObjWork(unsigned char *p) {
    return *(int *)(p + 0x30);
}
