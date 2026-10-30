/* GAMECORE.XFF @ 0x0F7E08 (48 B) - getPathColiGroupByType
 * Evidence: loads $v0, -0x3740($v1), $v0, -0x373C($v1); relocs <.bss>, <.bss>+0x3740, <.bss>+0x373C
 
 */
/* UNCONFIRMED: .bss+0x1C8C0 / +0x1C8C4 hold the two path collision group ids. */
extern int D_kernel_bss_1C8C0;
extern int D_kernel_bss_1C8C4;

int getPathColiGroupByType(int type) {
    if (type == 0)
        return D_kernel_bss_1C8C0;
    if (type == 1)
        return D_kernel_bss_1C8C4;
    return 0;
}
