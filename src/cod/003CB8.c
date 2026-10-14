/* asm/cod/003CB8.s -> func_00105948.
 * clean; w45a_1 (R2)
 * MATCHED (Session 8). */
extern char D_00136B00[];   /* lui/%lo */
extern char D_00136B10[];   /* lui/%lo */
extern char D_0013A018[];   /* lui/%lo */
extern char D_0013A020[];   /* lui/%lo */
extern char D_0013A028[];   /* lui/%lo */

void func_00105948(int a0, int a1, ...);
void func_00105990(int a0, int a1, ...);
int  func_0010EC38(int a0, int a1, int a2);

int func_00103CB8(int a0, int a1, int a2) {
    int r;

    func_00105948(0x4080FF00, (int)D_00136B00, a2);
    func_00105948(0x80C0FF00, (int)D_0013A018, a0);
    func_00105990(0x4080FF00, (int)D_0013A020);
    r = func_0010EC38(a0, a1, a2);
    if (r < 0) {
        func_00105990(0xFF804000, (int)D_00136B10, a0, r);
        return -1;
    }
    func_00105990(0x4080FF00, (int)D_0013A028);
    return 0;
}
