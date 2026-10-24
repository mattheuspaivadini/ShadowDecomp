/* MANAGER.XFF @ 0x061128 (8 B) - charrootdyn_getUpperEdgeEffectiveHeight
 * Evidence: `jr $ra` with `ac800098` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
void charrootdyn_getUpperEdgeEffectiveHeight(unsigned char *p) {
    *(int *)(p + 0x98) = 0;
}
