/* GAMECORE.XFF @ 0x0E2FE8 (8 B) - get_lws_animation_collision_group_cameraman
 * Evidence: `jr $ra` with `8c820014` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int get_lws_animation_collision_group_cameraman(unsigned char *p) {
    return *(int *)(p + 0x14);
}
