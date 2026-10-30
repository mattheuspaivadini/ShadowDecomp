/* GAMECORE.XFF @ 0x0238D8 (28 B) - getAreaSize
 * Evidence: lwc1 +0x40 * cvt.s.w(+0x38) at .data+0xA90
 * UNCONFIRMED: int/float typing of +0x38
 */
extern char D_kernel_data_0A90[];

float getAreaSize(void) {
    char *p = D_kernel_data_0A90;
    return *(float *)(p + 0x40) * (float)*(int *)(p + 0x38);
}
