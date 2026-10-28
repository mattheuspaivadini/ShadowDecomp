/* GAMECORE.XFF @ 0x007AC8 (12 B) - getSnapShotNum
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x60) - returns the object address.
 */
extern char D_kernel_data_0060[];

int getSnapShotNum(void) {
    return (int)D_kernel_data_0060;
}
