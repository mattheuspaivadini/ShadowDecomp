/* GAMECORE.XFF @ 0x0C53A0 (12 B) - getMinAngleWeak
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x181c) - returns the object address.
 */
extern char D_kernel_data_181C[];

int getMinAngleWeak(void) {
    return (int)D_kernel_data_181C;
}
