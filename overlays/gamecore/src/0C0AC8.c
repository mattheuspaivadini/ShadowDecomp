/* GAMECORE.XFF @ 0x0C0AC8 (56 B) - bosslifebar_display
 * Evidence: loads $f0, 0x17B8($v0), $f0, 0x17A8($v0); relocs <.data>, <.data>+0x17B8, <.data>+0x17A8
 
 */
extern char D_kernel_data_17A8[];
extern char D_kernel_data_17B8[];

int bosslifebar_display(void) {
    int r = 0;
    if (*(float *)(D_kernel_data_17B8) > 0.0f ||
        *(float *)(D_kernel_data_17A8) > 0.0f)
        r = 1;
    return r;
}
