/* GAMECORE.XFF @ 0x00BE78 (28 B) - ReleaseGame
 * Evidence: clears bits ~a0 in gcGlobalVar+0x1AC
 * UNCONFIRMED: none
 */
extern int gcGlobalVar[];

void ReleaseGame(int mask) {
    gcGlobalVar[0x1AC / 4] &= ~mask;
}
