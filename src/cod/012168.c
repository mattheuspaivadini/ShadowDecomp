/* func_00112168 @ 0x00112168 (0x24 bytes): stack buffer + call
 * func_00107410(2, &buf). */
void Deci2Call(int op, int *buf);

void sceDeci2Close(int a) {
    int buf;

    buf = a;
    Deci2Call(2, &buf);
}
