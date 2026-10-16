/* asm/cod/00ACD0.s -> func_0010A798.
 * 3-way validation, inverted last test; w45a_2 (R2)
 * MATCHED (Session 8). */
extern int D_00132314 __attribute__((section(".data")));
extern int D_001459C0[];
extern int D_00146600[];
extern int D_001470C0[];

int func_0010A798(int a0);
int sceFsInit(void);
int func_0010AAC8(void);
int func_0010A120(void);
int func_0010A7C8(void);
int func_0010A228(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8, int a9);

int sceFsSetIopPrio(int a0) {
    int r;

    func_0010A798(0xFD);
    if (D_00132314 == 0)
        sceFsInit();
    if (func_0010AAC8() != 0) {
        func_0010A7C8();
        return 0xFFFEFFFC;
    }
    if (func_0010A120() != 0) {
        func_0010A7C8();
        return -0x10;
    }
    D_001459C0[0] = a0;
    r = func_0010A228((int)D_001470C0, 0xFD, 0, (int)D_001459C0, 8,
                      (int)D_00146600, 4, 0, 0, 0);
    if (r < 0) {
        func_0010A7C8();
        return -0xB;
    }
    r = *(int *)((unsigned int)D_00146600 | 0x20000000);
    func_0010A7C8();
    return r;
}
