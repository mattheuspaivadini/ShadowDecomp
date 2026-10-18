/* asm/cod/00F3C8.s -> InitTLBFunctions.
 * InitTLBFunctions; TLB table as a pair-struct array + void setter prototype (Session 22)
 * MATCHED. */
void func_0010F3B8(int a0, int a1);
int func_0010F360(int a0, void *a1, int a2);
int FlushCache(int a0);
int func_0010F3A8(int a0);

struct tlbpair { int a; int b; };
extern struct tlbpair D_001326B8[];
extern int _kExecArg[];   /* lui/%lo -> non-small */
extern int D_00132338[];   /* lui/addiu -> non-small */

void InitTLBFunctions(void) {
    unsigned int i;
    struct tlbpair *p;

    p = D_001326B8;
    func_0010F3B8(p[0].a, p[0].b);
    func_0010F360(0x80075000, D_00132338, 0x330);
    FlushCache(0);
    FlushCache(2);
    func_0010F3B8(p[1].a, p[1].b);
    func_0010F3B8(p[2].a, p[2].b);
    for (i = 3; i < 8; i++) {
        func_0010F3B8(p[i].a, func_0010F3A8(p[i].a));
    }
    _kExecArg[0] = func_0010F3A8(3);
}
