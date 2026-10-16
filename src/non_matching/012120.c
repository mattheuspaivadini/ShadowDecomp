/* STATUS (10, 2026-10-16): NON_MATCHING. best score 5 [cc=29].
 * 
 * The original .s stays in the build (asm/cod/012120.s); this C
 * draft (10) is kept for the record. */
void Deci2Call(int op, int *buf);

/* func_00112120 @ 0x00112120 (0x44 bytes): op 1, buffer (u16 a0, a1, a2,
 * D_0014AE88 | 0x20000000). */
extern char D_0014AE88[];

void sceDeci2Open(unsigned short a0, int a1, int a2) {
    int buf[4];

    buf[0] = a0;
    buf[1] = a1;
    buf[2] = a2;
    buf[3] = (int)D_0014AE88 | 0x20000000;
    Deci2Call(1, buf);
}
