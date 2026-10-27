/* GAMECORE.XFF @ 0x008BD8 (8 B) - convert_from_button_value_to_bool
 * Evidence: `jr $ra` with `0004102b` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int convert_from_button_value_to_bool(unsigned int value) {
    return value != 0;
}
