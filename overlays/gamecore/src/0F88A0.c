/* GAMECORE.XFF @ 0x0F88A0 (8 B) - setAttainRadPathWork
 * Evidence: `jr $ra` with `e48c00e4` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setAttainRadPathWork(unsigned char *p, float value) {
    *(float *)(p + 0xe4) = value;
}
