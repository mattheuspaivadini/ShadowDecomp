/* GAMECORE.XFF @ 0x112F10 (8 B) - setGroundFrictionCoffWormCtrlWork
 * Evidence: `jr $ra` with `e48c0090` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setGroundFrictionCoffWormCtrlWork(unsigned char *p, float value) {
    *(float *)(p + 0x90) = value;
}
