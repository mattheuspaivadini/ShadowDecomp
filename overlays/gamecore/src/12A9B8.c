/* GAMECORE.XFF @ 0x12A9B8 (8 B) - setWormIKBankInterpSec
 * Evidence: `jr $ra` with `e48c128c` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setWormIKBankInterpSec(unsigned char *p, float value) {
    *(float *)(p + 0x128c) = value;
}
