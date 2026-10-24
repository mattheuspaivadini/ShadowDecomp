/* GAMECORE.XFF @ 0x0D7648 (8 B) - end_rewind_camera_dist_to_look_at
 * Evidence: `jr $ra` with `ac800030` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void end_rewind_camera_dist_to_look_at(unsigned char *p) {
    *(int *)(p + 0x30) = 0;
}
