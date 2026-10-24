/* MANAGER.XFF @ 0x051450 (8 B) - resetOutsideScriptCtrlStatus
 * Evidence: `jr $ra` with `fc800928` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
void resetOutsideScriptCtrlStatus(unsigned char *p) {
    *(unsigned long *)(p + 0x928) = 0;
}
