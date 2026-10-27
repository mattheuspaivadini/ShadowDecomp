/* GAMECORE.XFF @ 0x0E2F08 (8 B) - set_camera_mode
 * Evidence: `jr $ra` with `ac850004` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void set_camera_mode(unsigned char *p, int value) {
    *(int *)(p + 0x4) = value;
}
