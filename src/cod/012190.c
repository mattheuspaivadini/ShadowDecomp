void func_00107410(int op, int *buf);

/* func_00112190 @ 0x00112190 (0x30 bytes): op 3, (a0, (signed char)a1). */
void func_00112190(int a0, signed char a1) {
    int buf[2];

    buf[0] = a0;
    buf[1] = a1;
    func_00107410(3, buf);
}
