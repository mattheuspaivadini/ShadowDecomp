/* MANAGER.XFF @ 0x0092C0 (8 B) - set_rot_radi_value_flag_double_spring_interp_cntrl
 * Evidence: `jr $ra` with `ac850014` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
void set_rot_radi_value_flag_double_spring_interp_cntrl(unsigned char *p, int value) {
    *(int *)(p + 0x14) = value;
}
