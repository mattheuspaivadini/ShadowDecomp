/* MANAGER.XFF @ 0x0E9228 (8 B) - get_screen_width
 * Evidence: `jr $ra` with `8c820000` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
int get_screen_width(unsigned char *p) {
    return *(int *)(p + 0x0);
}
