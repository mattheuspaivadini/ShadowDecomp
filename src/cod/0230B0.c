/* asm/cod/0230B0.s -> func_00109D28 (cc=29).
 * Void wrapper + void tail callee: the 0x30 (2.9) frame + `j`
 * MATCHED (Session 7). */
/* v01: both the wrapper and the tail callee void (sibling-call eligibility). */
extern int D_00169F10[];
extern int D_00169F58[];

void sceSifRemoveRpc(int a0, int a1);
void sceSifRemoveRpcQueue(int a0);
void TerminateThread(int a0);
void DeleteThread(int a0);

void sce_delete_callback_thread(int a0) {
    sceSifRemoveRpc((int)D_00169F10, (int)D_00169F58);
    sceSifRemoveRpcQueue((int)D_00169F58);
    TerminateThread(a0);
    DeleteThread(a0);
}
