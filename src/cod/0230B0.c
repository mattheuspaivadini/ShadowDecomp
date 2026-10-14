/* asm/cod/0230B0.s -> func_00109D28 (cc=29).
 * Void wrapper + void tail callee: the 0x30 (2.9) frame + `j`
 * MATCHED (Session 7). */
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
