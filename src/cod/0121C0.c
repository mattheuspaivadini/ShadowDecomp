/* func_001121C0 @ 0x001121C0 (0x24 bytes): stack buffer + call
 * func_00107410(4, &buf). */
void Deci2Call(int op, int *buf);

void sceDeci2Poll(int a) {
    int buf;

    buf = a;
    Deci2Call(4, &buf);
}
