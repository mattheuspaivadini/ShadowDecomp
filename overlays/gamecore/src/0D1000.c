/* GAMECORE.XFF @ 0x0D1000 (12 B) - getLogLineColorR
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x1ad0) - returns the object address.
 */
extern char D_kernel_data_1AD0[];

int getLogLineColorR(void) {
    return (int)D_kernel_data_1AD0;
}
