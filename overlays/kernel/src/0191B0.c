/* KERNEL.XFF @ 0x0191B0 (12 B) - getSpriteDrawFirst
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x668) - returns the object address.
 */
extern char D_kernel_data_0668[];

int getSpriteDrawFirst(void) {
    return (int)D_kernel_data_0668;
}
