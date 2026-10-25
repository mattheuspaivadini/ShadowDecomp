/* KERNEL.XFF @ 0x011B60 (36 B) - resetArcFuncCall
 * Evidence: four .data words (0x434..0x440) cleared with four separate lui
 * pairs; the register order (first lui -> 0x434 in the delay slot) is that of
 * one chained assignment. UNCONFIRMED: object names.
 */
extern int D_kernel_data_0434;
extern int D_kernel_data_0438;
extern int D_kernel_data_043C;
extern int D_kernel_data_0440;

void resetArcFuncCall(void) {
    D_kernel_data_0434 = D_kernel_data_0438 = D_kernel_data_043C = D_kernel_data_0440 = 0;
}
