/* KERNEL.XFF @ 0x003D20 (12 B) - getMemorySafetyLockFlag
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0xbc) - returns the object address.
 */
extern char D_kernel_data_00BC[];

int getMemorySafetyLockFlag(void) {
    return (int)D_kernel_data_00BC;
}
