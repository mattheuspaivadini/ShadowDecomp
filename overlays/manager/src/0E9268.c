/* MANAGER.XFF @ 0x0E9268 (8 B) - get_view_angle
 * Evidence: `jr $ra` with `c480000c` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
float get_view_angle(unsigned char *p) {
    return *(float *)(p + 0xc);
}
