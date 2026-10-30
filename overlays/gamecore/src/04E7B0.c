/* GAMECORE.XFF @ 0x04E7B0 (12 B) - getBloodEffectEnableFlag
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x1144) - returns the object address.
 */
extern char D_kernel_data_1144[];

int getBloodEffectEnableFlag(void) {
    return (int)D_kernel_data_1144;
}
