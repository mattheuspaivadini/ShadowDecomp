/* KERNEL.XFF @ 0x01FD58 (36 B) - Sg2DspEffectSetSwitch
 * Evidence: sibling Sg2RemoteSend(9, 0, core, on). UNCONFIRMED: Sg2RemoteSend prototype (command, then three words).
 */
int Sg2RemoteSend(int cmd, int a, int b, int c);

int Sg2DspEffectSetSwitch(int core, int on) {
    return Sg2RemoteSend(9, 0, core, on);
}
