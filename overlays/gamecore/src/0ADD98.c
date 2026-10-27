/* GAMECORE.XFF @ 0x0ADD98 (8 B) - Kite_SetAnimalID_KitePathWork
 * Evidence: `jr $ra` with `ac850000` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void Kite_SetAnimalID_KitePathWork(unsigned char *p, int value) {
    *(int *)(p + 0x0) = value;
}
