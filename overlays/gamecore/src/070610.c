/* GAMECORE.XFF @ 0x070610 (8 B) - get_hope_yaw_nico_sight_on
 * Evidence: `jr $ra` with `c4800208` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
float get_hope_yaw_nico_sight_on(unsigned char *p) {
    return *(float *)(p + 0x208);
}
