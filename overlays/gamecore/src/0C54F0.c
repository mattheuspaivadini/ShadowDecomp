/* GAMECORE.XFF @ 0x0C54F0 (12 B) - getSwordGlowDistMax
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x1908) - returns the object address.
 */
extern char D_kernel_data_1908[];

int getSwordGlowDistMax(void) {
    return (int)D_kernel_data_1908;
}
