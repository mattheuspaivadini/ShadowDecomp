/* KERNEL.XFF @ 0x016260 (12 B) - getCRTCoffsetV
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x60c) - returns the object address.
 */
extern char D_kernel_data_060C[];

int getCRTCoffsetV(void) {
    return (int)D_kernel_data_060C;
}
