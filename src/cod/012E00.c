/* func_00112E00 @ 0x00112E00 (0x3C bytes): shift five arguments right and
 * forward (a0, 0, a1..a5) to func_00112CC8. */
int func_00112CC8(int a, int b, int c, int d, int e, int f, int g);

int sceSifSendCmd(int a0, int a1, int a2, int a3, int a4, int a5) {
    return func_00112CC8(a0, 0, a1, a2, a3, a4, a5);
}
