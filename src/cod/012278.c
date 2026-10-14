/* func_00112278 @ 0x00112278 (0x34 bytes): same as 012240 with op -6. */
void func_00107410(int op, int *buf);

void func_00112278(int a0, int a1, unsigned short a2) {
    int buf[3];

    buf[0] = a0;
    buf[1] = a1;
    buf[2] = a2;
    func_00107410(-6, buf);
}
