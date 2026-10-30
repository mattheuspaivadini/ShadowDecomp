/* GAMECORE.XFF @ 0x112DF8 (56 B) - setAttainSpeedWormCtrlWork
 * Evidence: stores $f12, 0xB0($a0); loads $f0, 0x58($a0)
 
 */
/* UNCONFIRMED: +0x58 is the speed upper limit, +0xB0 the stored attain speed. */
int setAttainSpeedWormCtrlWork(char *p, float speed) {
    if (speed >= 0.0f && speed <= *(float *)(p + 0x58)) {
        *(float *)(p + 0xB0) = speed;
        return 1;
    }
    return 0;
}
