/* GAMECORE.XFF @ 0x0705A0 (8 B) - get_base_pitch_nico_sight_on
 * Evidence: `jr $ra` with `c4800284` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
float get_base_pitch_nico_sight_on(unsigned char *p) {
    return *(float *)(p + 0x284);
}
