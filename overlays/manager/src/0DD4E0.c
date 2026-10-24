/* MANAGER.XFF @ 0x0DD4E0 (8 B) - seSetVol
 * Evidence: `jr $ra` with `e48c0018` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
void seSetVol(unsigned char *p, float value) {
    *(float *)(p + 0x18) = value;
}
