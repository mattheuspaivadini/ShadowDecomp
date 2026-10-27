/* GAMECORE.XFF @ 0x0F8990 (8 B) - getWayForRoute
 * Evidence: `jr $ra` with `8c82040c` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int getWayForRoute(unsigned char *p) {
    return *(int *)(p + 0x40c);
}
