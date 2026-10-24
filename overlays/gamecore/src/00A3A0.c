/* GAMECORE.XFF @ 0x00A3A0 (8 B) - GAMEUTIL_set_parameter_position_filter
 * Evidence: `jr $ra` with `e48c0024` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void GAMEUTIL_set_parameter_position_filter(unsigned char *p, float value) {
    *(float *)(p + 0x24) = value;
}
