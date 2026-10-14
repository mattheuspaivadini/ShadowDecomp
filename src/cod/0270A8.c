/* func_001270A8 @ 0x001270A8 (0x2C bytes): pack four words into a stack
 * buffer and forward to func_00127390. */
int func_00127390(void *buf);

int func_001270A8(int a0, int a1, int a2, int a3) {
    int buf[4];

    buf[0] = a0;
    buf[1] = a1;
    buf[2] = a2;
    buf[3] = a3;
    return func_00127390(buf);
}
