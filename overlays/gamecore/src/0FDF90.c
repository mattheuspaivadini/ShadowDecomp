/* GAMECORE.XFF @ 0x0FDF90 (40 B) - calcTurnTime2
 * Evidence: stores $ra, 0x0($sp); loads $v0, 0x1C($a0), $f14, 0xA4($a0), $v1, 0x0($v0), $f13, 0xA8($a0), $f15, 0x78($v1), $ra, 0x0($sp); calls j calcAngleTime; frame
 
 */
/* UNCONFIRMED: +0x1C points at a work whose +0x00 is the owner, +0xA4/+0xA8 are
 * the turn limits; the incoming angle is forwarded as the first argument.
 */
void calcAngleTime(float angle, float a, float b, float c);

void calcTurnTime2(char *p, float angle) {
    char *work = *(char **)(p + 0x1C);
    char *owner = *(char **)work;
    calcAngleTime(angle, *(float *)(p + 0xA8), *(float *)(p + 0xA4),
                  *(float *)(owner + 0x78));
}
