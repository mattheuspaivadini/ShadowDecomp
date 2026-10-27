/* GAMECORE.XFF @ 0x009E68 (8 B) - GAMEUTIL_reset_move_angle
 * Evidence: `jr $ra` with `ac800000` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void GAMEUTIL_reset_move_angle(unsigned char *p) {
    *(int *)(p + 0x0) = 0;
}
