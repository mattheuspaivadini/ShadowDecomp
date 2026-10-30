/* GAMECORE.XFF @ 0x0077E8 (12 B) - getForceMemoryAllocSize
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x0) - returns the object address.
 */
extern char D_kernel_data_0000[];

int getForceMemoryAllocSize(void) {
    return (int)D_kernel_data_0000;
}
