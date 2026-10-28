/* GAMECORE.XFF @ 0x0242C0 (12 B) - GetSeamlessStageObjectGroup
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0xafc) - returns the object address.
 */
extern char D_kernel_data_0AFC[];

int GetSeamlessStageObjectGroup(void) {
    return (int)D_kernel_data_0AFC;
}
