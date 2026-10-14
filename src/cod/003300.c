/* func_00103300 @ 0x00103300 (0x3C bytes): func_00129200(a0,
 * D_0013A000, 6) then return (ret == 0) ? a0 + 6 : 0. */
int func_00129200(int a0, const char *s, int n);

extern char D_0013A000[];

int func_00103300(int a0) {
    int ret = func_00129200(a0, D_0013A000, 6);
    int r = a0 + 6;

    if (ret != 0)
        r = 0;
    return r;
}
