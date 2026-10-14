/* func_0011BA28 @ 0x0011BA28 (0x3C bytes): as the family, with a u16
 * third argument (andi a2,0xFFFF in the jal delay) and the same early-return
 * tail shape. */
int func_0011B150(int a0, int a1, unsigned short a2);
int func_0011B670(int a, int b, int *out);

int func_0011BA28(int a0, int a1, unsigned short a2) {
    int v = func_0011B150(a0, a1, a2);

    if (v != 0)
        return v;
    func_0011B670(0, 0, &v);
    return v;
}
