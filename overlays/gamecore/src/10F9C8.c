/* GAMECORE.XFF @ 0x10F9C8 (8 B) - setAttainMotScaleSlowLegCtrlWork
 * Evidence: `jr $ra` with `e48c0040` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setAttainMotScaleSlowLegCtrlWork(unsigned char *p, float value) {
    *(float *)(p + 0x40) = value;
}
