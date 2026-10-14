/* func_00112240 @ 0x00112240 (0x34 bytes): pack (a0,a1,(u16)a2) and call
 * func_00107410(-5, &buf). */
void func_00107410(int op, int *buf);

void func_00112240(int a0, int a1, unsigned short a2) {
    int buf[3];

    buf[0] = a0;
    buf[1] = a1;
    buf[2] = a2;
    func_00107410(-5, buf);
}
