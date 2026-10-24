/* MANAGER.XFF @ 0x0E7C48 (8 B) - get_clip_screen
 * Evidence: `jr $ra` with `8c820250` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
int get_clip_screen(unsigned char *p) {
    return *(int *)(p + 0x250);
}
