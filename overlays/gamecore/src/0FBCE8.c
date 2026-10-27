/* GAMECORE.XFF @ 0x0FBCE8 (8 B) - setGpCalcDist
 * Evidence: `jr $ra` with `e48c3c84` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setGpCalcDist(unsigned char *p, float value) {
    *(float *)(p + 0x3c84) = value;
}
