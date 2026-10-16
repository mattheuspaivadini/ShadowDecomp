void Deci2Call(int op, int *buf);

/* func_001122B0 @ 0x001122B0 (0x30 bytes): op -7, (a0, (signed char)a1). */
void sceDeci2ExReqSend(int a0, signed char a1) {
    int buf[2];

    buf[0] = a0;
    buf[1] = a1;
    Deci2Call(-7, buf);
}
