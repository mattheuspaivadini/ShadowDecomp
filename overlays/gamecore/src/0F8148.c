/* GAMECORE.XFF @ 0x0F8148 (8 B) - setRouteColCheckPathWork
 * Evidence: `jr $ra` with `ac850390` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setRouteColCheckPathWork(unsigned char *p, int value) {
    *(int *)(p + 0x390) = value;
}
