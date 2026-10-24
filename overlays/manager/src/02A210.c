/* MANAGER.XFF @ 0x02A210 (8 B) - spriteSetPriority
 * Evidence: `jr $ra` with `a085004c` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
void spriteSetPriority(unsigned char *p, char value) {
    *(char *)(p + 0x4c) = value;
}
