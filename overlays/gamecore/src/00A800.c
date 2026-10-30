/* GAMECORE.XFF @ 0x00A800 (12 B) - getSightOnRevCntrlLR
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x220) - returns the object address.
 */
extern char D_kernel_data_0220[];

int getSightOnRevCntrlLR(void) {
    return (int)D_kernel_data_0220;
}
