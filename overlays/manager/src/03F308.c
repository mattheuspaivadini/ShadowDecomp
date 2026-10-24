/* MANAGER.XFF @ 0x03F308 (8 B) - is_doit_neck_turn_need
 * Evidence: `jr $ra` with `8c820030` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
int is_doit_neck_turn_need(unsigned char *p) {
    return *(int *)(p + 0x30);
}
