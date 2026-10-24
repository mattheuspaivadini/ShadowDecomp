/* GAMECORE.XFF @ 0x0F8070 (8 B) - getRealColJudgeFunc
 * Evidence: `jr $ra` with `8c823c54` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int getRealColJudgeFunc(unsigned char *p) {
    return *(int *)(p + 0x3c54);
}
