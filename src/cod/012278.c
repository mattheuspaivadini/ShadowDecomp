/* func_00112278 @ 0x00112278 (0x34 bytes): same as 012240 with op -6. */
void Deci2Call(int op, int *buf);

void sceDeci2ExSend(int a0, int a1, unsigned short a2) {
    int buf[3];

    buf[0] = a0;
    buf[1] = a1;
    buf[2] = a2;
    Deci2Call(-6, buf);
}
