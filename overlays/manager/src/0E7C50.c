/* MANAGER.XFF @ 0x0E7C50 (8 B) - get_transform_matrix_set
 * Evidence: `jr $ra` with `8c820254` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
int get_transform_matrix_set(unsigned char *p) {
    return *(int *)(p + 0x254);
}
