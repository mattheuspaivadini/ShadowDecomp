void Deci2Call(int op, int *buf);

/* func_00112330 @ 0x00112330 (0x24 bytes): op 0x10, one-word buffer. */
void kputs(int a0) {
    int buf;

    buf = a0;
    Deci2Call(0x10, &buf);
}
