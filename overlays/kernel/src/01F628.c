/* KERNEL.XFF @ 0x01F628 (52 B) - Sg2ChipInit
 * Evidence: Sg2CtrlSetTickTime(0); Sg2RemoteSend(0x11, 0, 0, 0); returns 0. UNCONFIRMED: Sg2RemoteSend prototype (command, then three words).
 */
int Sg2RemoteSend(int cmd, int a, int b, int c);
void Sg2CtrlSetTickTime(int t);

int Sg2ChipInit(void) {
    Sg2CtrlSetTickTime(0);
    Sg2RemoteSend(0x11, 0, 0, 0);
    return 0;
}
