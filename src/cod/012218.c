/* func_00112218 @ 0x00112218 (0x24 bytes): stack buffer + call
 * func_00107410(0x21, &buf). */
void Deci2Call(int op, int *buf);

void sceDeci2GrpClose(int a) {
    int buf;

    buf = a;
    Deci2Call(0x21, &buf);
}
