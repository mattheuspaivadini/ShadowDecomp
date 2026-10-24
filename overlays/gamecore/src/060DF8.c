/* GAMECORE.XFF @ 0x060DF8 (8 B) - MotSpdCtrl_SetParam
 * Evidence: `jr $ra` with `ac850014` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void MotSpdCtrl_SetParam(unsigned char *p, int value) {
    *(int *)(p + 0x14) = value;
}
