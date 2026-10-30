/* GAMECORE.XFF @ 0x0129D0 (20 B) - demoscrCheckDemoFinish
 * Evidence: padManagerData+8 & 0x800
 * UNCONFIRMED: none
 */
extern int padManagerData[];

static inline int to_bool(unsigned int v) {
    return v != 0;
}

int demoscrCheckDemoFinish(void) {
    return to_bool(padManagerData[2] & 0x800);
}
