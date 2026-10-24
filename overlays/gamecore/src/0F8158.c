/* GAMECORE.XFF @ 0x0F8158 (8 B) - setPlayerWayColCheckPathWork
 * Evidence: `jr $ra` with `ac850398` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setPlayerWayColCheckPathWork(unsigned char *p, int value) {
    *(int *)(p + 0x398) = value;
}
