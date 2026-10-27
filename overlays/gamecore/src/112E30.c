/* GAMECORE.XFF @ 0x112E30 (8 B) - setAttackParamWormCtrlWork
 * Evidence: `jr $ra` with `e48c00b8` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setAttackParamWormCtrlWork(unsigned char *p, float value) {
    *(float *)(p + 0xb8) = value;
}
