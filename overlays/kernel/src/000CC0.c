/* KERNEL.XFF @ 0x000CC0 (116 B) - iosGetCpuRapCountPar1Int
 * Evidence: (float)(unsigned)T0_COUNT (0x10000800; the bltz path is GCC's unsigned-to-float) * 60.0f / the float table at .data+0x98 indexed by the mode word at .data+0x94 (set by iosResetCpuRapCounter). UNCONFIRMED: table name.
 */
extern int D_kernel_data_0094;
extern float D_kernel_data_0098[];

float iosGetCpuRapCountPar1Int(void) {
    return (float)*(volatile unsigned int *)0x10000800 * 60.0f / D_kernel_data_0098[D_kernel_data_0094];
}
