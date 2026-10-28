/* GAMECORE.XFF @ 0x007AF8 (12 B) - getDebugSnapShotSizeX
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x6c) - returns the object address.
 */
extern char D_kernel_data_006C[];

int getDebugSnapShotSizeX(void) {
    return (int)D_kernel_data_006C;
}
