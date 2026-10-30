/* GAMECORE.XFF @ 0x018208 (20 B) - gameflowMpegCancelChk
 * Evidence: (padManagerData+8 >> 11) & 1
 * UNCONFIRMED: none
 */
extern int padManagerData[];

int gameflowMpegCancelChk(void) {
    return (padManagerData[2] >> 11) & 1;
}
