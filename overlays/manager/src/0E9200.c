/* MANAGER.XFF @ 0x0E9200 (8 B) - set_view_angle
 * Evidence: `jr $ra` with `e48c000c` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
void set_view_angle(unsigned char *p, float value) {
    *(float *)(p + 0xc) = value;
}
