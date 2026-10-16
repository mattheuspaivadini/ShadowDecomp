void Deci2Call(int op, int *buf);

/* func_001122E0 @ 0x001122E0 (0x24 bytes): op -8, one-word buffer. */
void sceDeci2ExLock(int a0) {
    int buf;

    buf = a0;
    Deci2Call(-8, &buf);
}
