/* MANAGER.XFF @ 0x0166B8 (8 B) - iosSetKPrintfDlContext
 * Evidence: `jr $ra` with `ac850038` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
void iosSetKPrintfDlContext(unsigned char *p, int value) {
    *(int *)(p + 0x38) = value;
}
