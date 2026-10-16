/* asm/cod/028490.s -> func_00106ED0.
 * session9 R1 w25b/wcg wave
 * MATCHED (Session 8). */
extern int D_001360C0[];         /* .data 0x001360C0: lui/addiu %lo */
extern int D_001360C4[];         /* .data 0x001360C4: lui/addiu %lo */
extern int __sce_sema_id[];         /* .data 0x001329A0: lui + lw %lo */

extern int GetThreadId(int a0);
extern void WaitSema(int a0);

void __malloc_lock(int a0) {
    int t;

    t = GetThreadId(a0);
    if (D_001360C0[0] == t) {
        D_001360C4[0] = D_001360C4[0] + 1;
        return;
    }
    WaitSema(__sce_sema_id[0]);
    D_001360C0[0] = t;
    D_001360C4[0] = D_001360C4[0] + 1;
}
