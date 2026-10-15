/* asm/cod/028490.s -> func_00106ED0.
 * session9 R1 w25b/wcg wave
 * MATCHED (Session 8). */
extern int D_001360C0[];         /* .data 0x001360C0: lui/addiu %lo */
extern int D_001360C4[];         /* .data 0x001360C4: lui/addiu %lo */
extern int D_001329A0[];         /* .data 0x001329A0: lui + lw %lo */

extern int func_00106ED0(int a0);
extern void func_00107020(int a0);

void func_00128490(int a0) {
    int t;

    t = func_00106ED0(a0);
    if (D_001360C0[0] == t) {
        D_001360C4[0] = D_001360C4[0] + 1;
        return;
    }
    func_00107020(D_001329A0[0]);
    D_001360C0[0] = t;
    D_001360C4[0] = D_001360C4[0] + 1;
}
