/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 2 [cc=29, default, variant best_void].
 * cc=29 keeps jal+epilogue (+1 instruction) while the image has a 2.9-style 0x30 frame AND a tail `j`; cc=296 sibling-calls but packs an 8-byte frame.
 * The original .s stays in the build (asm/cod/0230B0.s); this C
 * draft (Session 7) is kept for the record. */
/* v01: both the wrapper and the tail callee void (sibling-call eligibility). */
extern int D_00169F10[];
extern int D_00169F58[];

void func_00109D28(int a0, int a1);
void func_00109DC0(int a0);
void func_00106E30(int a0);
void func_00106DF0(int a0);

void func_001230B0(int a0) {
    func_00109D28((int)D_00169F10, (int)D_00169F58);
    func_00109DC0((int)D_00169F58);
    func_00106E30(a0);
    func_00106DF0(a0);
}
