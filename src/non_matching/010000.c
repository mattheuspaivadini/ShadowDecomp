/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 25 [cc=29].
 * R2 w45a_3: reg-alloc (5-arg descriptor call)
 * The original .s stays in the build (asm/cod/010000.s); this C
 * draft (Session 8) is kept for the record. */
int func_0010FFF0(int a0, int a1, int a2, int a3, int a4);
int func_0010FFB0(int a0, int a1, int a2);
int func_001290C4(int a0);

extern int _kExecArg[];   /* lui/%lo -> non-small */
extern int D_00133168[];   /* lui/addiu -> non-small */

int func_00110000(int a0, int a1, int *a2) {
    int arg;
    int n;
    int len;
    int base;
    int end;

    base = _kExecArg[0];
    end = base + 0x40;
    func_0010FFF0(D_00133168[0], D_00133168[1], (int)a2, (int)D_00133168,
                  end);
    n = a1 < 0x10 ? 0xF : a1;
    func_0010FFB0(base, (int)&arg, 4);
    base += 4;
    len = func_001290C4(a0) + 1;
    func_0010FFB0(arg, a0, len);
    arg += len;
    if (n > 0) {
        do {
            func_0010FFB0(base, (int)&arg, 4);
            base += 4;
            n--;
            len = func_001290C4(*a2) + 1;
            func_0010FFB0(arg, *a2, len);
            a2++;
            arg += len;
        } while (n != 0);
    }
    return end;
}
