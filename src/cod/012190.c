void Deci2Call(int op, int *buf);

/* func_00112190 @ 0x00112190 (0x30 bytes): op 3, (a0, (signed char)a1). */
void sceDeci2ReqSend(int a0, signed char a1) {
    int buf[2];

    buf[0] = a0;
    buf[1] = a1;
    Deci2Call(3, buf);
}
