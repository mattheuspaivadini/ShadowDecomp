/* KERNEL.XFF @ 0x01F660 (44 B) - Sg2ChipInitHot
 * Evidence: Sg2RemoteSend(0x11, 1, 0, 0); returns 0. UNCONFIRMED: Sg2RemoteSend prototype (command, then three words).
 */
int Sg2RemoteSend(int cmd, int a, int b, int c);

int Sg2ChipInitHot(void) {
    Sg2RemoteSend(0x11, 1, 0, 0);
    return 0;
}
