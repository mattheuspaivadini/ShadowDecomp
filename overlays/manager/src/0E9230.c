/* MANAGER.XFF @ 0x0E9230 (8 B) - get_screen_height
 * Evidence: `jr $ra` with `8c820004` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
int get_screen_height(unsigned char *p) {
    return *(int *)(p + 0x4);
}
