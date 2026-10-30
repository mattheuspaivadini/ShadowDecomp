/* GAMECORE.XFF @ 0x0D8490 (36 B) - reset_camera_vs_ofst_cntrl_param_segment_array
 * Evidence: `lui 0x2 / addiu -0x3E28` (bss+0x1C1D8), `$a1 = 0`, `$a2 = 0x28`, tail `j
 * memset`.
 * UNCONFIRMED: none
 
 */
extern char D_kernel_bss_1C1D8[];
void *memset(void *dst, int c, unsigned int n);

void reset_camera_vs_ofst_cntrl_param_segment_array(void) {
    memset(D_kernel_bss_1C1D8, 0, 0x28);
}
