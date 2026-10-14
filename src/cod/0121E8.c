/* MATCHED (Session 6, cc=29): the original frame is 0x30 with `ra` at 0x20,
 * so the buffer is 0x20 bytes (8 ints), not the 3 the Session-5 attempt
 * declared; and the first two stores are emitted in the order 1, 0.
 * Both were found with tools/const_diff.py (frame size) + the permuter.
 *
 * asm/cod/0121E8.s -> func_001121E8 @ 0x001121E8 (0x30 bytes) */
void func_00107410(int op, int *buf);

void func_001121E8(unsigned char a0, int a1, int a2) {
    int buf[8];

    buf[1] = a1;
    buf[0] = a0;
    buf[2] = a2;
    func_00107410(0x20, buf);
}
