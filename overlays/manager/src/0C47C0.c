/* MANAGER.XFF @ 0x0C47C0 (8 B) - get_main_particle_effect_lod_from_sheet
 * Evidence: `jr $ra` with `8c820048` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
int get_main_particle_effect_lod_from_sheet(unsigned char *p) {
    return *(int *)(p + 0x48);
}
