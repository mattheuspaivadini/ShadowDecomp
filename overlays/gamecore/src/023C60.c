/* GAMECORE.XFF @ 0x023C60 (12 B) - getSeamlessStageHighModelDispDist
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0xa64) - returns the object address.
 */
extern char D_kernel_data_0A64[];

int getSeamlessStageHighModelDispDist(void) {
    return (int)D_kernel_data_0A64;
}
