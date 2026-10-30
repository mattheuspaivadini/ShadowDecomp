/* GAMECORE.XFF @ 0x0E3508 (28 B) - get_main_cameraman
 * Evidence: bss+0x1C200 index read, then element at idx*4+8
 * UNCONFIRMED: field names/types guessed from offsets
 */
extern struct { int idx, pad, obj[1]; } D_kernel_bss_1C200;
int get_main_cameraman(void) {
    return D_kernel_bss_1C200.obj[D_kernel_bss_1C200.idx];
}
