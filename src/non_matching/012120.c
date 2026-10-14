/* STATUS (Session 5, step 2): NON_MATCHING - best attempt [cc=296] is not byte-exact.
 * 5 instructions: OR of the static address and the 0x20000000 flag.
 * See docs/progress.md for the family classification. */
void func_00107410(int op, int *buf);

/* func_00112120 @ 0x00112120 (0x44 bytes): op 1, buffer (u16 a0, a1, a2,
 * D_0014AE88 | 0x20000000). */
extern char D_0014AE88[];

void func_00112120(unsigned short a0, int a1, int a2) {
    int buf[4];

    buf[0] = a0;
    buf[1] = a1;
    buf[2] = a2;
    buf[3] = (int)D_0014AE88 | 0x20000000;
    func_00107410(1, buf);
}
