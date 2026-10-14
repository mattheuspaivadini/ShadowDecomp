/* asm/cod/003D88.s -> func_00105948.
 * clean; w45a_1 (R2)
 * MATCHED (Session 8). */
extern char D_00136B48[];   /* lui/%lo */
extern char D_00136B58[];   /* lui/%lo */
extern char D_0013A018[];   /* lui/%lo */
extern char D_0013A020[];   /* lui/%lo */
extern char D_0013A028[];   /* lui/%lo */
extern char D_0013A030[];   /* lui/%lo */

void func_00105948(int a0, int a1, ...);
void func_00105990(int a0, int a1, ...);
int  func_0010E8A0(int a0);
int  func_0010E608(int a0, int a1, int a2, int *a3);
int  func_0010E810(int a0);

int func_00103D88(int a0, int a1, int a2, int *a3) {
    int h;
    int v;
    int buf;

    func_00105948(0x4080FF00, (int)D_00136B48, a2);
    func_00105948(0x80C0FF00, (int)D_0013A018, a0);
    func_00105990(0x4080FF00, (int)D_0013A020);
    h = func_0010E8A0(a0);
    if (h >= 0) {
        v = func_0010E608(h, 1, (int)D_0013A030, a3 != 0 ? a3 : &buf);
        if (v >= 0)
            v = func_0010E810(h);
    } else {
        v = h;
    }
    if (v < 0) {
        func_00105990(0xFF804000, (int)D_00136B58, a0, v);
        return -1;
    }
    func_00105990(0x4080FF00, (int)D_0013A028);
    return v;
}
