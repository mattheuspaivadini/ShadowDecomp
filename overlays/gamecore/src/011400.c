/* GAMECORE.XFF @ 0x011400 (12 B) - getDemoEnableFlag
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x734) - returns the object address.
 */
extern char D_kernel_data_0734[];

int getDemoEnableFlag(void) {
    return (int)D_kernel_data_0734;
}
