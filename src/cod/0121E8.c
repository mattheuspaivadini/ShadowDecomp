/* asm/cod/0121E8.s -> func_001121E8 @ 0x001121E8 (0x30 bytes, 12 insns)
 *
 * Packs (a0 & 0xFF, a1, a2) into a 4-word stack block and forwards it to
 * func_00107410(0x20, &buf). The original's frame is 0x30 bytes (buf[8]).
 *
 * MATCHED (Session 6, step 1) with cc=29 (2.9-ee-991111-01). The store order
 * in the source is load-bearing: buf[1] first, then buf[0], then buf[2] in the
 * jal delay slot. Baseline (buf[0] first) is 4 instructions off.
 */
void func_00107410(int op, int *buf);

void func_001121E8(unsigned char a0, int a1, int a2) {
    int buf[8];

    buf[1] = a1;
    buf[0] = a0;
    buf[2] = a2;
    func_00107410(0x20, buf);
}
