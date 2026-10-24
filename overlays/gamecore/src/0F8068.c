/* GAMECORE.XFF @ 0x0F8068 (8 B) - setRealColJudgeFunc
 * Evidence: `jr $ra` with `ac853c54` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setRealColJudgeFunc(unsigned char *p, int value) {
    *(int *)(p + 0x3c54) = value;
}
