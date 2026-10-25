/* KERNEL.XFF @ 0x01EA38 (56 B) - soundSetRevMode
 * Evidence: sg2NicoReverbMode |= bits when the first argument is 0, else &= ~bits.
 */
extern int sg2NicoReverbMode;

void soundSetRevMode(int clear, int bits) {
    if (clear == 0) {
        sg2NicoReverbMode |= bits;
    } else {
        sg2NicoReverbMode &= ~bits;
    }
}
