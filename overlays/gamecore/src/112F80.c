/* GAMECORE.XFF @ 0x112F80 (8 B) - setColOffsetJudgeFunc
 * Evidence: `jr $ra` with `ac8500f0` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setColOffsetJudgeFunc(unsigned char *p, int value) {
    *(int *)(p + 0xf0) = value;
}
