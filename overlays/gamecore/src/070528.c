/* GAMECORE.XFF @ 0x070528 (8 B) - get_ofst_yaw_nico_sight_on
 * Evidence: `jr $ra` with `c4800248` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
float get_ofst_yaw_nico_sight_on(unsigned char *p) {
    return *(float *)(p + 0x248);
}
