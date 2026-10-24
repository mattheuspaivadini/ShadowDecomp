/* MANAGER.XFF @ 0x0166B0 (8 B) - iosSetKPrintfDynamicsContext
 * Evidence: `jr $ra` with `ac850034` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
void iosSetKPrintfDynamicsContext(unsigned char *p, int value) {
    *(int *)(p + 0x34) = value;
}
