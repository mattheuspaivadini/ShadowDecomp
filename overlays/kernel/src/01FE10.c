/* KERNEL.XFF @ 0x01FE10 (48 B) - Sg2DspSetMasterVolumeMax
 * Evidence: the static at .text+0x1FD80 is called for core 0 and core 1 with (0x3FFF, 0x3FFF). UNCONFIRMED: callee name (master volume setter).
 */
int func_01FD80(int core, int l, int r);

void Sg2DspSetMasterVolumeMax(void) {
    func_01FD80(0, 0x3FFF, 0x3FFF);
    func_01FD80(1, 0x3FFF, 0x3FFF);
}
