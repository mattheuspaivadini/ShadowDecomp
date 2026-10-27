/* GAMECORE.XFF @ 0x0F80F0 (8 B) - setExecRayChkPathWork
 * Evidence: `jr $ra` with `ac850384` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setExecRayChkPathWork(unsigned char *p, int value) {
    *(int *)(p + 0x384) = value;
}
