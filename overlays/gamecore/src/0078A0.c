/* GAMECORE.XFF @ 0x0078A0 (12 B) - getDispCollisionPerfFlag
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0xc) - returns the object address.
 */
extern char D_kernel_data_000C[];

int getDispCollisionPerfFlag(void) {
    return (int)D_kernel_data_000C;
}
