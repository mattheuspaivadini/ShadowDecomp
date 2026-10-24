/* GAMECORE.XFF @ 0x0F8140 (8 B) - setForceRouteAttrPathWork
 * Evidence: `jr $ra` with `ac85038c` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setForceRouteAttrPathWork(unsigned char *p, int value) {
    *(int *)(p + 0x38c) = value;
}
