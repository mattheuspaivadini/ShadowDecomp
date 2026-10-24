/* MANAGER.XFF @ 0x0C47C8 (8 B) - get_sub_particle_effect_lod_from_sheet
 * Evidence: `jr $ra` with `8c82004c` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
int get_sub_particle_effect_lod_from_sheet(unsigned char *p) {
    return *(int *)(p + 0x4c);
}
