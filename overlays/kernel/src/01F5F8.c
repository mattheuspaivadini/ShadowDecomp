/* KERNEL.XFF @ 0x01F5F8 (44 B) - Sg2ChipSetDigitalOutputMode
 * Evidence: Sg2RemoteSend(5, 1, mode, 0); returns 0. UNCONFIRMED: Sg2RemoteSend prototype (command, then three words).
 */
int Sg2RemoteSend(int cmd, int a, int b, int c);

int Sg2ChipSetDigitalOutputMode(int mode) {
    Sg2RemoteSend(5, 1, mode, 0);
    return 0;
}
