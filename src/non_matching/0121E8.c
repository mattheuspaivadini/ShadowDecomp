/* STATUS (Session 5, step 2): NON_MATCHING - best attempt [cc=29] is not byte-exact.
 * 8 instructions: `andi a0` placement / store order.
 * See docs/progress.md for the family classification. */
void func_00107410(int op, int *buf);

/* func_001121E8 @ 0x001121E8 (0x30 bytes): op 0x20, (u8 a0, a1, a2). */
void func_001121E8(unsigned char a0, int a1, int a2) {
    int buf[3];

    buf[0] = a0;
    buf[1] = a1;
    buf[2] = a2;
    func_00107410(0x20, buf);
}
