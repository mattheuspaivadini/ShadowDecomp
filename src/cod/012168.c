/* func_00112168 @ 0x00112168 (0x24 bytes): stack buffer + call
 * func_00107410(2, &buf). */
void func_00107410(int op, int *buf);

void func_00112168(int a) {
    int buf;

    buf = a;
    func_00107410(2, &buf);
}
