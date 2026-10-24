/* MANAGER.XFF @ 0x0C47D0 (8 B) - get_top_particle_effect_from_lod
 * Evidence: `jr $ra` with `8c8200d4` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
int get_top_particle_effect_from_lod(unsigned char *p) {
    return *(int *)(p + 0xd4);
}
