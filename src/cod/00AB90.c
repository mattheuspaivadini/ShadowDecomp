/* asm/cod/00AB90.s -> func_0010A798.
 * 3-way validation, err/ok block layout; w45a_2 (R2)
 * MATCHED (Session 8). */
extern int D_00132314 __attribute__((section(".data")));
extern int D_001459C0[];
extern int D_00146600[];
extern int D_001470C0[];

int func_0010A798(int a0);
int func_0010A8C0(void);
int func_0010AAC8(void);
int func_0010A120(void);
int func_0010A7C8(void);
int func_0010A228(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8, int a9);

int func_0010AB90(int a0, int a1) {
    int r;

    func_0010A798(0xFE);
    if (D_00132314 == 0)
        func_0010A8C0();
    if (func_0010AAC8() != 0) {
        func_0010A7C8();
        return 0xFFFEFFFC;
    }
    if (func_0010A120() != 0) {
        func_0010A7C8();
        return -0x10;
    }
    if ((a0 & 0x3FFF) != 0 || a0 == 0 || (unsigned int)a0 > 0xFFFFF ||
        a1 == 0 || (unsigned int)a1 >= 0x21) {
        func_0010A7C8();
        return -0x16;
    }
    D_001459C0[0] = a0;
    D_001459C0[1] = a1;
    r = func_0010A228((int)D_001470C0, 0xFE, 0, (int)D_001459C0, 8,
                      (int)D_00146600, 4, 0, 0, 0);
    if (r < 0) {
        func_0010A7C8();
        return -0xB;
    }
    r = *(int *)((unsigned int)D_00146600 | 0x20000000);
    func_0010A7C8();
    return r;
}
