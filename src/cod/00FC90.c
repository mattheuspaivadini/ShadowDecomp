/* asm/cod/00FC90.s -> GetSystemCallEntry.
 * GetSystemCallEntry cc=29
 * MATCHED (Session 12). */
int func_0010FBF8(int *dst, int *src, int n);

extern int D_00132988[];

int GetSystemCallEntry(int idx) {
    int buf;

    func_0010FBF8(&buf, (int *)(D_00132988[0] + idx * 4), 4);
    return buf;
}
