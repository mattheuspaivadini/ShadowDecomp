/* GAMECORE.XFF @ 0x0F8150 (8 B) - setRouteLockPathWork
 * Evidence: `jr $ra` with `ac850394` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setRouteLockPathWork(unsigned char *p, int value) {
    *(int *)(p + 0x394) = value;
}
