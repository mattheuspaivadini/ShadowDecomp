/* GAMECORE.XFF @ 0x112F00 (8 B) - setFallGravCoffWormCtrlWork
 * Evidence: `jr $ra` with `e48c0088` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setFallGravCoffWormCtrlWork(unsigned char *p, float value) {
    *(float *)(p + 0x88) = value;
}
