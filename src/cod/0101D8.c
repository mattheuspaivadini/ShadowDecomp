/* asm/cod/0101D8.s -> func_00110118 (cc=29).
 * Void prototypes for both callees make cc=29 emit the tail `j` (the 2.9 0x20 frame + sibling call).
 * MATCHED (Session 7). */
/* v01: void prototypes for the wrapper and the tail callee. */
void func_00110118(int a0);
void _Exit(int a0);

void Exit(int a0) {
    int saved = a0;

    func_00110118(a0);
    _Exit(saved);
}
