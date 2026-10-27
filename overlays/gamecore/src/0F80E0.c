/* GAMECORE.XFF @ 0x0F80E0 (8 B) - setRayByRealColPathWork
 * Evidence: `jr $ra` with `ac8500f0` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setRayByRealColPathWork(unsigned char *p, int value) {
    *(int *)(p + 0xf0) = value;
}
