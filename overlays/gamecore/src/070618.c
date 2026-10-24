/* GAMECORE.XFF @ 0x070618 (8 B) - get_hope_pitch_nico_sight_on
 * Evidence: `jr $ra` with `c4800204` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
float get_hope_pitch_nico_sight_on(unsigned char *p) {
    return *(float *)(p + 0x204);
}
