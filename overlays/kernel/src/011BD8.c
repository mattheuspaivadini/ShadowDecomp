/* KERNEL.XFF @ 0x011BD8 (72 B) - iosGetTableCos
 * Evidence: The 16384-entry float table at .bss+0xE6C0 covers a quarter turn; abs() of the 16-bit angle (expand_abs gives the bltzl/negu pair), mirrored as 0x8000 - i with a sign flip past 0x4000. UNCONFIRMED: table name.
 */
int abs(int x);
extern float D_kernel_bss_E6C0[];

float iosGetTableCos(short angle) {
    int i = angle;
    float f;
    int neg = 0;

    i = abs(i);
    if (i >= 0x4000) {
        neg = 1;
        i = 0x8000 - i;
    }
    f = D_kernel_bss_E6C0[i];
    if (neg) {
        f = -f;
    }
    return f;
}
