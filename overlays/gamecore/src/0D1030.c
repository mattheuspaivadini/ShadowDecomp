/* GAMECORE.XFF @ 0x0D1030 (12 B) - getLogLineColorA
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x1adc) - returns the object address.
 */
extern char D_kernel_data_1ADC[];

int getLogLineColorA(void) {
    return (int)D_kernel_data_1ADC;
}
