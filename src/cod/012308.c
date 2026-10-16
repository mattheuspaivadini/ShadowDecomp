void Deci2Call(int op, int *buf);

/* func_00112308 @ 0x00112308 (0x24 bytes): op -9, one-word buffer. */
void sceDeci2ExUnLock(int a0) {
    int buf;

    buf = a0;
    Deci2Call(-9, &buf);
}
