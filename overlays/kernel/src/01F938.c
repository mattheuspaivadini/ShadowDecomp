/* KERNEL.XFF @ 0x01F938 (44 B) - Sg2DmaTransVoice
 * Evidence: sibling Sg2RemoteSendDmaCom(0x13, a, b, c) (arguments shifted up one register). UNCONFIRMED: prototype.
 */
int Sg2RemoteSendDmaCom(int cmd, void *a, void *b, int c);

int Sg2DmaTransVoice(void *a, void *b, int c) {
    return Sg2RemoteSendDmaCom(0x13, a, b, c);
}
