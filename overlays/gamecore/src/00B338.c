/* GAMECORE.XFF @ 0x00B338 (12 B) - getScissoringScreenSize
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x5e4) - returns the object address.
 */
extern char D_kernel_data_05E4[];

int getScissoringScreenSize(void) {
    return (int)D_kernel_data_05E4;
}
