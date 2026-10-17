/* asm/cod/028510.s -> __malloc_unlock.
 * SCE recursive lock over __sce_sema_id (counterpart of 028490)
 * MATCHED. */
extern int D_001360C0[];         /* .data 0x001360C0: owner thread */
extern int D_001360C4[];         /* .data 0x001360C4: recursion count */
extern int __sce_sema_id[];      /* .data 0x001329A0 */

extern int SignalSema(int sema_id);

void __malloc_unlock(int a0) {
    if (--D_001360C4[0] == 0) {
        D_001360C0[0] = -1;
        SignalSema(__sce_sema_id[0]);
    }
}
