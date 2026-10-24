/* MANAGER.XFF @ 0x0166C0 (8 B) - iosSetKPrintfScaleContext
 * Evidence: `jr $ra` with `e48c003c` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
void iosSetKPrintfScaleContext(unsigned char *p, float value) {
    *(float *)(p + 0x3c) = value;
}
