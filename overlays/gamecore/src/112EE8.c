/* GAMECORE.XFF @ 0x112EE8 (8 B) - setObstacleWormCtrlWork
 * Evidence: `jr $ra` with `ac8500e0` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setObstacleWormCtrlWork(unsigned char *p, int value) {
    *(int *)(p + 0xe0) = value;
}
