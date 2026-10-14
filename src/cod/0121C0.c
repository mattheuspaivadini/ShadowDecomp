/* func_001121C0 @ 0x001121C0 (0x24 bytes): stack buffer + call
 * func_00107410(4, &buf). */
void func_00107410(int op, int *buf);

void func_001121C0(int a) {
    int buf;

    buf = a;
    func_00107410(4, &buf);
}
