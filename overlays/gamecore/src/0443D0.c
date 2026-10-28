/* GAMECORE.XFF @ 0x0443D0 (12 B) - getBosstatusDispMode
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x10f0) - returns the object address.
 */
extern char D_kernel_data_10F0[];

int getBosstatusDispMode(void) {
    return (int)D_kernel_data_10F0;
}
