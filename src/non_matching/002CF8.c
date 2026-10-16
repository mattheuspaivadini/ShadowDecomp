/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 21 [cc=29].
 * R1 wave3e: fmt route through $v0 before the call
 * The original .s stays in the build (asm/cod/002CF8.s); this C
 * draft (Session 8) is kept for the record. */
void func_0012C048(void *ctx, int fmt, void *ap);
void func_001285C0(char *buf);
void func_001290C4(char *buf);

void LoaderSysPrintf(int fmt, ...) {
    char buf[0x100];

    func_0012C048(buf, fmt, __builtin_saveregs());
    func_001285C0(buf);
    func_001290C4(buf);
}
