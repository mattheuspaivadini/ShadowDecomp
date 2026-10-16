/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 26 [cc=29].
 * R4 w25a_0: varargs register-save area (frame 0xC0)
 * The original .s stays in the build (asm/cod/008EF8.s); this C
 * draft (Session 8) is kept for the record. */
int  DIntr(void);
void EIntr(void);
int  func_00107FF8(int (*cb)(), int *p, int a1, int a2, int a3);
int  func_00108D68(int a, int b, int c);

void scePrintf(int a0, ...) {
    int buf;
    int g;

    buf = 0;
    g = DIntr();
    func_00107FF8(func_00108D68, &buf, 0xFFFFFFFF, a0,
                  (int)__builtin_saveregs());
    if (g != 0)
        EIntr();
}
