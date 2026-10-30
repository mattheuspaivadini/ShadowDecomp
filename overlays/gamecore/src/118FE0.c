/* GAMECORE.XFF @ 0x118FE0 (64 B) - SCRFuncChangeSegmentVariation
 * Evidence: stores $s0, 0x0($sp), $ra, 0x8($sp); loads $s0, 0x0($sp), $ra, 0x8($sp); calls stagemanager_getSegmentVariation, j stagemanager_changeSegmentVariation; frame
 
 */
/* UNCONFIRMED: only the 2nd argument is used; the variation change is skipped
 * when the segment is already on the requested variation.
 */
int stagemanager_getSegmentVariation(void);
void stagemanager_changeSegmentVariation(int variation);

void SCRFuncChangeSegmentVariation(void *unused, int variation) {
    if (variation != stagemanager_getSegmentVariation())
        stagemanager_changeSegmentVariation(variation);
}
