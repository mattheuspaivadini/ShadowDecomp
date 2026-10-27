/* KERNEL.XFF @ 0x01D9F8 (56 B) - isysSleepSubThreadM
 * Evidence: calls the static at .text+0x1D4B4 n times (loop.c count-down, bnez). UNCONFIRMED: callee name.
 */
void func_01D4B4(void);

void isysSleepSubThreadM(int n) {
    int i;

    for (i = 0; i < n; i++) {
        func_01D4B4();
    }
}
