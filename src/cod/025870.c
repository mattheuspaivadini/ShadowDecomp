/* func_00125870 @ 0x00125870 (0x2C bytes): pack (a0,a1,a2) + 64-bit a3
 * into a stack buffer and forward to func_001270D8. */
int func_001270D8(void *buf);

struct S025870 {
    int f0;
    int f4;
    int f8;
    int pad;
    long long w10;
};

int func_00125870(int a0, int a1, int a2, long long a3) {
    struct S025870 buf;

    buf.f0 = a0;
    buf.f4 = a1;
    buf.f8 = a2;
    buf.w10 = a3;
    return func_001270D8(&buf);
}
