/* GAMECORE.XFF @ 0x00C000 (12 B) - getGameAnimeTimeScaleRatio
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x5f0) - returns the object address.
 */
extern char D_kernel_data_05F0[];

int getGameAnimeTimeScaleRatio(void) {
    return (int)D_kernel_data_05F0;
}
