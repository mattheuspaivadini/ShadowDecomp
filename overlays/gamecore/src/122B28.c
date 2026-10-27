/* GAMECORE.XFF @ 0x122B28 (8 B) - setPerceptionParam
 * Evidence: `jr $ra` with `ac850040` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setPerceptionParam(unsigned char *p, int value) {
    *(int *)(p + 0x40) = value;
}
