/* GAMECORE.XFF @ 0x009FA8 (8 B) - GAMEUTIL_get_cur_velocity_move_angle
 * Evidence: `jr $ra` with `c4800000` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
float GAMEUTIL_get_cur_velocity_move_angle(unsigned char *p) {
    return *(float *)(p + 0x0);
}
