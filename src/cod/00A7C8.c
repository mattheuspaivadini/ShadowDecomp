/* asm/cod/00A7C8.s -> func_0010A7C8.
 * SignalSema tail call
 * MATCHED (Session 12). */
extern __attribute__((section(".data"))) int D_0013231C;
int SignalSema(int semid);

void func_0010A7C8(void) {
    SignalSema(D_0013231C);
}
