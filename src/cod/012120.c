/* asm/cod/012120.s -> sceDeci2Open.
 * SCE deci2: returns the Deci2Call result (Session 19)
 * MATCHED. */
int Deci2Call(int op, int *buf);

/* sceDeci2Open @ 0x00112120 (0x44 bytes): op 1, buffer (u16 a0, a1, a2,
 * D_0014AE88 | 0x20000000). */
extern char D_0014AE88[];

int sceDeci2Open(unsigned short a0, int a1, int a2) {
    int buf[4];

    buf[0] = a0;
    buf[1] = a1;
    buf[2] = a2;
    buf[3] = (int)D_0014AE88 | 0x20000000;
    return Deci2Call(1, buf);
}
