/* func_001190F8 @ 0x001190F8 (0x40 bytes): func_00118380(a0, 0x10, out, 0,
 * 4); negative -> -0x21E, else *out. */
int func_00118380(int a0, int a1, int *out, int a3, int a4);

int sceInetAbortLog(int a0, int *out) {
    int r = func_00118380(a0, 0x10, out, 0, 4);

    if (r < 0)
        return -0x21E;
    return *out;
}
