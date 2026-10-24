/* GAMECORE.XFF @ 0x030C08 (8 B) - bgmStopChk
 * Evidence: `jr $ra` with `0080102d` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int bgmStopChk(int value) {
    return value;
}
