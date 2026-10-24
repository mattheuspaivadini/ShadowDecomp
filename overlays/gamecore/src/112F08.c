/* GAMECORE.XFF @ 0x112F08 (8 B) - setMaxFallSpeedWormCtrlWork
 * Evidence: `jr $ra` with `e48c008c` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setMaxFallSpeedWormCtrlWork(unsigned char *p, float value) {
    *(float *)(p + 0x8c) = value;
}
