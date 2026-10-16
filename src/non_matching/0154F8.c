/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 26 [cc=wine:ee-gcc2.95.2-273a].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/0154F8.s); this C
 * draft (Session 9) is kept for the record. */
struct B0154F8 {
    int w0;     /* 0x00 */
    int w1;     /* 0x04 */
    int w2;     /* 0x08 */
    int w3;     /* 0x0C */
};

extern char D_0014B598[];   /* non-small: lui/addiu %lo, records of 0x334 */

int scePad2GetButtonInfo(int index, unsigned char *data, int sub) {
    struct B0154F8 t;

    t = *(struct B0154F8 *)(D_0014B598 + index * 0x334 + sub * 16 + 0x14);
    if (t.w0 == 0)
        return -1;
    if (t.w1 == 1) {
        int b;

        b = (data[t.w2] >> t.w3) & 1;
        return b ? 0 : 1;
    }
    if (t.w1 == 8) {
        int v;

        v = (data[t.w2] >> t.w3) & 0xFF;
        if (t.w3 != 0) {
            t.w2 = t.w2 + 1;
            v = (v | (data[t.w2] << (8 - t.w3))) & 0xFF;
        }
        return v;
    }
    return -1;
}
