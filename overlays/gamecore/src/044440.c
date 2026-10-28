/* GAMECORE.XFF @ 0x044440 (12 B) - getBoneCollisionDebugMode
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x10f4) - returns the object address.
 */
extern char D_kernel_data_10F4[];

int getBoneCollisionDebugMode(void) {
    return (int)D_kernel_data_10F4;
}
