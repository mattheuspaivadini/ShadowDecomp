/* GAMECORE.XFF @ 0x00B348 (12 B) - getPlayerAliveInPauseFlag
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x5e8) - returns the object address.
 */
extern char D_kernel_data_05E8[];

int getPlayerAliveInPauseFlag(void) {
    return (int)D_kernel_data_05E8;
}
