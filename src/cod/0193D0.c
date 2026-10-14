/* func_001193D0 @ 0x001193D0 (0x40 bytes): same as 0190F8 with op 0x1E. */
int func_00118380(int a0, int a1, int *out, int a3, int a4);

int func_001193D0(int a0, int *out) {
    int r = func_00118380(a0, 0x1E, out, 0, 4);

    if (r < 0)
        return -0x21E;
    return *out;
}
