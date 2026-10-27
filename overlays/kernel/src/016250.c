/* KERNEL.XFF @ 0x016250 (12 B) - getCRTCoffsetU
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x608) - returns the object address.
 */
extern char D_kernel_data_0608[];

int getCRTCoffsetU(void) {
    return (int)D_kernel_data_0608;
}
