/* MANAGER.XFF @ 0x07E890 (8 B) - SetLwoDemoOrientManagerObjCutFinishFlag
 * Evidence: `jr $ra` with `ac8500b0` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
void SetLwoDemoOrientManagerObjCutFinishFlag(unsigned char *p, int value) {
    *(int *)(p + 0xb0) = value;
}
