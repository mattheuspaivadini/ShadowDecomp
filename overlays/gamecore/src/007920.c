/* GAMECORE.XFF @ 0x007920 (12 B) - getPlayerPowerDisp
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x24) - returns the object address.
 */
extern char D_kernel_data_0024[];

int getPlayerPowerDisp(void) {
    return (int)D_kernel_data_0024;
}
