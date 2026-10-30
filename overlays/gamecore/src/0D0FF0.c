/* GAMECORE.XFF @ 0x0D0FF0 (12 B) - getSprLogStatusAddress
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x1ac0) - returns the object address.
 */
extern char D_kernel_data_1AC0[];

int getSprLogStatusAddress(void) {
    return (int)D_kernel_data_1AC0;
}
