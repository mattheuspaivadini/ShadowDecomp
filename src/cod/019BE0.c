/* asm/cod/019BE0.s -> SceMrpcBind.
 * constant 0x2000 fixed + byte-exact under EE-GCC 2.95.3-136
 * MATCHED (Session 8). */
int SceMrpcBind(int a, int b, int c, int d, int e, int f);

void func_00119BE0(int a, int b, int c) {
    SceMrpcBind(a, b, c, 0x800, 0x2000, 0x20);
}
