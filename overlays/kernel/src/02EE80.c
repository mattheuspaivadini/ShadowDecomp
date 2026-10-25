/* KERNEL.XFF @ 0x02EE80 (52 B) - Sg2ExPcmInputOpenDoubleBuffer
 * Evidence: forwards to the static at .text+0x2ED28 as (a, size, size / 2, c, 1, 0, 0, 0) (signed halving: srl 31 + addu + sra 1; the last four in $t0..$t3). UNCONFIRMED: callee prototype.
 */
int func_02ED28(int a, int b, int c, int d, int e, int f, int g, int h);

int Sg2ExPcmInputOpenDoubleBuffer(int a, int size, int c) {
    return func_02ED28(a, size, size / 2, c, 1, 0, 0, 0);
}
