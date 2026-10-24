/* GAMECORE.XFF @ 0x10F9C0 (8 B) - setMotScaleMaxSlowLegCtrlWork
 * Evidence: `jr $ra` with `e48c0038` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setMotScaleMaxSlowLegCtrlWork(unsigned char *p, float value) {
    *(float *)(p + 0x38) = value;
}
