/* GAMECORE.XFF @ 0x107B08 (8 B) - setGazeCoffGazeCtrlWork
 * Evidence: `jr $ra` with `e48c0010` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setGazeCoffGazeCtrlWork(unsigned char *p, float value) {
    *(float *)(p + 0x10) = value;
}
