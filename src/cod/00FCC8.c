/* asm/cod/00FCC8.s -> func_0010FDC8.
 * two-list walk + sltu sentinel store; w45a_3 (R2)
 * MATCHED (Session 8). */
int func_0010FDC8(int a0, int a1);
int func_0010FC80(unsigned int a0, unsigned int a1, void (*a2)());
void func_0010FC40(void);
void func_0010FC08(void);

extern int D_00132990[];   /* lui/%lo -> non-small */
extern int D_00132988[];   /* lui/%lo -> non-small */

void func_0010FCC8(void) {
    unsigned int a;
    unsigned int b;
    unsigned int x;
    unsigned int y;

    func_0010FDC8(D_00132990[0], D_00132990[1]);
    func_0010FDC8(D_00132990[2], D_00132990[3]);
    a = (unsigned int)func_0010FC80(0x80000000u, 0x80080000u, func_0010FC40);
    b = (unsigned int)func_0010FC80(0x80000000u, 0x80080000u, func_0010FC08);
    x = a - 0x20C;
    y = b - 0x168;
    while (x != y) {
        if (x < y) {
            a = (unsigned int)func_0010FC80(a + 4, 0x80080000u,
                                            func_0010FC40);
            x = a - 0x20C;
        } else {
            b = (unsigned int)func_0010FC80(b + 4, 0x80080000u,
                                            func_0010FC08);
            y = b - 0x168;
        }
    }
    D_00132988[0] = (int)x;
}
