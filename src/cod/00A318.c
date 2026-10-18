/* asm/cod/00A318.s -> func_0010A318.
 * SIF table lookup under sema; early unlock+return 0 for out-of-range id (Session 22)
 * MATCHED. */
struct S16 { int f0, f4, f8, fC; };
extern int D_00132320[];
extern struct S16 D_00146EC0[];
void func_0010A0B0(void);
int WaitSema(int sema);
int SignalSema(int sema);

struct S16 *func_0010A318(unsigned int id) {
    struct S16 *p;

    func_0010A0B0();
    WaitSema(D_00132320[0]);
    if (id >= 0x20) {
        SignalSema(D_00132320[0]);
        return 0;
    }
    p = &D_00146EC0[id];
    SignalSema(D_00132320[0]);
    return p;
}
