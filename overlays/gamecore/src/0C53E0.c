/* GAMECORE.XFF @ 0x0C53E0 (12 B) - getFogChangeSpeed
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x182c) - returns the object address.
 */
extern char D_kernel_data_182C[];

int getFogChangeSpeed(void) {
    return (int)D_kernel_data_182C;
}
