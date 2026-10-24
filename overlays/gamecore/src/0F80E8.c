/* GAMECORE.XFF @ 0x0F80E8 (8 B) - setPassageWideRayPathWork
 * Evidence: `jr $ra` with `ac8500f4` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setPassageWideRayPathWork(unsigned char *p, int value) {
    *(int *)(p + 0xf4) = value;
}
