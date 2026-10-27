/* GAMECORE.XFF @ 0x0F8160 (8 B) - setFollowModePathWork
 * Evidence: `jr $ra` with `ac85039c` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setFollowModePathWork(unsigned char *p, int value) {
    *(int *)(p + 0x39c) = value;
}
