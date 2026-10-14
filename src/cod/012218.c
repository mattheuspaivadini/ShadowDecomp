/* func_00112218 @ 0x00112218 (0x24 bytes): stack buffer + call
 * func_00107410(0x21, &buf). */
void func_00107410(int op, int *buf);

void func_00112218(int a) {
    int buf;

    buf = a;
    func_00107410(0x21, &buf);
}
