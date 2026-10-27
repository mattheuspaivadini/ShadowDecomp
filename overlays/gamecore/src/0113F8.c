/* GAMECORE.XFF @ 0x0113F8 (8 B) - CheckDemoCameraOrientFinished
 * Evidence: `jr $ra` with `8c820038` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int CheckDemoCameraOrientFinished(unsigned char *p) {
    return *(int *)(p + 0x38);
}
