/* GAMECORE.XFF @ 0x00A810 (12 B) - getSightOnRevCntrlUD
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x224) - returns the object address.
 */
extern char D_kernel_data_0224[];

int getSightOnRevCntrlUD(void) {
    return (int)D_kernel_data_0224;
}
