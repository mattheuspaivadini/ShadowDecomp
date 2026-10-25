/* KERNEL.XFF @ 0x025C20 (24 B) - Sg2SepPlay
 * Evidence: forwards a0..a3 to the static at .text+0x25C38 with a fifth argument 2 ($t0). UNCONFIRMED: callee prototype.
 */
int func_025C38(int a, int b, int c, int d, int mode);

int Sg2SepPlay(int a, int b, int c, int d) {
    return func_025C38(a, b, c, d, 2);
}
