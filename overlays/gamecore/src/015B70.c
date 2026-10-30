/* GAMECORE.XFF @ 0x015B70 (64 B) - _omakeGetFlagCls
 * Evidence: byte-identical to _gameFlagCls (015188) with `.bss+0xC5A`.
 * UNCONFIRMED: the flag byte array's name.
 
 */
extern unsigned char D_kernel_bss_0000[];

void _omakeGetFlagCls(int index) {
    unsigned char *p = D_kernel_bss_0000 + 0xC5A + index / 8;
    int mask = 1 << (index & 7);

    *p = *p & ~mask;
}
