/* GAMECORE.XFF @ 0x112F18 (8 B) - setUnderFrictionCoffWormCtrlWork
 * Evidence: `jr $ra` with `e48c0094` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setUnderFrictionCoffWormCtrlWork(unsigned char *p, float value) {
    *(float *)(p + 0x94) = value;
}
