/* GAMECORE.XFF @ 0x023C70 (12 B) - getSeamlessStageMiddleModelDispDist
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0xa68) - returns the object address.
 */
extern char D_kernel_data_0A68[];

int getSeamlessStageMiddleModelDispDist(void) {
    return (int)D_kernel_data_0A68;
}
