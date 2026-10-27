/* KERNEL.XFF @ 0x005F08 (40 B) - iosPadChkConnect
 * Evidence: `jal padSysGet` with $a1 = 0 (port forwarded), then the word at +0x118
 * of the returned object tested as `(unsigned)(x - 1) < 2` (values 1 or 2).
 * UNCONFIRMED: padSysGet prototype/return type and the field meaning.
 */
char *padSysGet(int port, int slot);
int iosPadChkConnect(int port) {
    return (unsigned int)(*(int *)(padSysGet(port, 0) + 0x118) - 1) < 2;
}
